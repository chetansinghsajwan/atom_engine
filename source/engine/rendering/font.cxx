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

    font::font(texture2d* atlas)
        : _atlas_texture{ atlas }
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

        std::vector<msdf_atlas::GlyphGeometry> glyphs;
        msdf_atlas::FontGeometry font_geometry = msdf_atlas::FontGeometry(&glyphs);
        i32 glyphs_loaded = font_geometry.loadCharset(msdfgen_font_handle, 1, charset_to_load);
        u32 glyphs_loaded_expected = charset_to_load.size();

        if (glyphs_loaded != glyphs_loaded_expected)
        {
            return runtime_error{ "failed ot load expected count of glyphs." };
        }

        msdf_atlas::TightAtlasPacker packer;
        packer.setPixelRange(2.0);
        packer.setMiterLimit(1.0);
        packer.setScale(40);
        i32 pack_result = packer.pack(glyphs.data(), (int)glyphs.size());

        if (pack_result != 0)
        {
            return runtime_error{ "failed to pack texture atlas." };
        }

        int width = 0;
        int height = 0;
        packer.getDimensions(width, height);

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
        generator.generate(glyphs.data(), glyphs.size());

        msdf_bitmap_const_ref_type bitmap = generator.atlasStorage();
        memory_view data{ bitmap.pixels, (usize)bitmap.width * (usize)bitmap.height * 3 };

        texture2d* texture_atlas = texture_factory::create_from_data(
            data, texture_format::rgb8, u32vec2{ bitmap.width, bitmap.height });

        return new font{ texture_atlas };
    }

    auto font::get_atlas_texture() -> texture2d*
    {
        return _atlas_texture;
    }

    auto font::get_char(u32 ch) -> texture_slice
    {
        return {};
    }
}
