module;
#include "msdfgen/msdfgen.h"
#include "msdf-atlas-gen/FontGeometry.h"
#include "msdf-atlas-gen/GlyphGeometry.h"

export module atom.engine:rendering.font;

import std;
import atom_core;
import :rendering.texture2d;

namespace atom::engine
{
    export using msdfgen::FontMetrics;
    export using msdf_atlas::GlyphGeometry;

    export class font
    {
    public:
        font();
        ~font();

    public:
        static auto load_from_file(
            string_view path) -> result<font*, runtime_error, filesystem::filesystem_error,
                                  filesystem::noentry_error>;

    public:
        auto get_atlas() -> texture2d*;
        auto get_glyphs() -> msdf_atlas::FontGeometry::GlyphRange;
        auto get_glyph(char ch) -> const GlyphGeometry*;
        auto get_metrics() -> const FontMetrics&;

    private:
        texture2d* _atlas;
        msdf_atlas::FontGeometry _msdf_font_geometry;
        std::vector<msdf_atlas::GlyphGeometry> _msdf_glyphs;
    };
}
