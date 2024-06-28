module;
#include "msdfgen/msdfgen.h"
#include "msdfgen/msdfgen-ext.h"
#include "msdf-atlas-gen/Charset.h"
#include "msdf-atlas-gen/TightAtlasPacker.h"
#include "msdf-atlas-gen/GlyphGeometry.h"
#include "msdf-atlas-gen/FontGeometry.h"
#include "msdf-atlas-gen/AtlasGenerator.h"
#include "msdf-atlas-gen/ImmediateAtlasGenerator.h"
#include "msdf-atlas-gen/BitmapAtlasStorage.h"
#include "msdf-atlas-gen/glyph-generators.h"

module atom.engine:rendering.font.impl;

import atom.core;
import :math;
import :rendering.font;
import :rendering.texture;
import :rendering.texture2d;
import :rendering.texture_factory;

namespace atom::engine
{
    template <typename function_type>
    class scope_function
    {
    public:
        scope_function(function_type&& func)
            : _func{ move(func) }
        {}

        ~scope_function()
        {
            _func();
        }

    private:
        function_type _func;
    };

    msdfgen::FreetypeHandle* _msdfgen_handle = nullptr;

    font::font()
        : _atlas{ nullptr }
        , _msdf_font_geometry{ &_msdf_glyphs }
        , _msdf_glyphs{}
    {}

    font::~font() {}

    auto font::load_from_file(string_view path)
        -> result<font*, runtime_error, filesystem::filesystem_error, filesystem::noentry_error>
    {
        if (_msdfgen_handle == nullptr)
        {
            _msdfgen_handle = msdfgen::initializeFreetype();
            contract_asserts(_msdfgen_handle != nullptr, "failed to initialize msdfgen.");
        }

        auto file_data_result = filesystem::read_file_bytes(path);
        if (file_data_result
                .is_error_any<filesystem::filesystem_error, filesystem::noentry_error>())
        {
            return { create_from_result, file_data_result };
        }

        dynamic_buffer file_data = move(file_data_result).get_value();

        msdfgen::FontHandle* msdfgen_font_handle =
            msdfgen::loadFontData(_msdfgen_handle, file_data.get_data(), file_data.get_size());

        if (msdfgen_font_handle == nullptr)
        {
            return runtime_error{ "failed to load font." };
        }

        scope_function msdfgen_font_handle_destroyer{ [&]
            { msdfgen::destroyFont(msdfgen_font_handle); } };

        const msdf_atlas::Charset& charset_to_load = msdf_atlas::Charset::ASCII;

        class font* font = new class font
        {};

        i32 glyphs_loaded =
            font->_msdf_font_geometry.loadCharset(msdfgen_font_handle, 1, charset_to_load);
        u32 glyphs_loaded_expected = charset_to_load.size();

        if (glyphs_loaded != glyphs_loaded_expected)
        {
            return runtime_error{ "failed ot load expected count of glyphs." };
        }

        msdf_atlas::TightAtlasPacker packer;
        packer.setPixelRange(2.0);
        packer.setMiterLimit(1.0);
        packer.setScale(40);

        i32 pack_result = packer.pack(font->_msdf_glyphs.data(), (int)font->_msdf_glyphs.size());
        if (pack_result != 0)
        {
            return runtime_error{ "failed to pack texture atlas." };
        }

        int width = 0;
        int height = 0;
        packer.getDimensions(width, height);

        constexpr bool is_msdf = true;
        constexpr bool is_mtsdf = false;

        if (is_msdf or is_mtsdf)
        {
            constexpr f32 default_angle_thresold = 3.0;
            constexpr usize lcg_multiplier = 6364136223846793005ull;
            constexpr usize lcg_increment = 1442695040888963407ull;
            constexpr u32 thread_count = 8;
            constexpr u64 coloring_seed = 0;
            constexpr bool expensive_coloring = false;

            if (expensive_coloring)
            {
                auto worker = [&](int i, int thread_num) -> bool
                {
                    u64 glyph_seed =
                        (lcg_multiplier * (coloring_seed ^ i) + lcg_increment) * !!coloring_seed;

                    font->_msdf_glyphs[i].edgeColoring(
                        msdfgen::edgeColoringInkTrap, default_angle_thresold, glyph_seed);

                    return true;
                };

                auto workload = msdf_atlas::Workload(worker, font->_msdf_glyphs.size());
                workload.finish(thread_count);
            }
            else
            {
                u64 glyph_seed = coloring_seed;
                for (msdf_atlas::GlyphGeometry& glyph : font->_msdf_glyphs)
                {
                    glyph_seed *= lcg_multiplier;
                    glyph.edgeColoring(
                        msdfgen::edgeColoringInkTrap, default_angle_thresold, glyph_seed);
                }
            }
        }

        // create atlas

        msdf_atlas::GeneratorAttributes attributes;
        attributes.config.overlapSupport = true;
        attributes.scanlinePass = true;

        using msdf_atlas_storage_type = msdf_atlas::BitmapAtlasStorage<byte, 3>;
        using msdf_bitmap_const_ref_type = msdfgen::BitmapConstRef<byte, 3>;
        using msdf_atlas_generator_type = msdf_atlas::ImmediateAtlasGenerator<float, 3,
            &msdf_atlas::msdfGenerator, msdf_atlas_storage_type>;

        msdf_atlas_generator_type generator{ width, height };
        generator.setAttributes(attributes);
        generator.setThreadCount(8);
        generator.generate(font->_msdf_glyphs.data(), font->_msdf_glyphs.size());

        msdf_bitmap_const_ref_type bitmap = generator.atlasStorage();
        memory_view data{ bitmap.pixels, (usize)bitmap.width * (usize)bitmap.height * 3 };

        font->_atlas = texture_factory::create_from_data(
            data, texture_format::rgb8, u32vec2{ bitmap.width, bitmap.height });

        return font;
    }

    auto font::get_atlas() -> texture2d*
    {
        return _atlas;
    }

    auto font::get_glyphs() -> msdf_atlas::FontGeometry::GlyphRange
    {
        return _msdf_font_geometry.getGlyphs();
    }

    auto font::get_glyph(char ch) -> const GlyphGeometry*
    {
        return _msdf_font_geometry.getGlyph(ch);
    }

    auto font::get_metrics() -> const FontMetrics&
    {
        return _msdf_font_geometry.getMetrics();
    }
}
