export module atom.engine:rendering.font;

import atom.core;
import :rendering.texture2d;

namespace atom::engine
{
    export class texture_slice
    {};

    export class font
    {
    public:
        font(texture2d* atlas);
        ~font();

    public:
        static auto load_from_file(
            string_view path) -> result<font*, runtime_error, filesystem::filesystem_error,
                                  filesystem::noentry_error>;

    public:
        auto get_atlas_texture() -> texture2d*;

        auto get_char(u32 ch) -> texture_slice;

    private:
        texture2d* _atlas_texture;
    };
}
