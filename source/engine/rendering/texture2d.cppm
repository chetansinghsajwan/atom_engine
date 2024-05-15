export module atom.engine:rendering.texture2d;

import atom.core;
import :rendering.texture;

namespace atom::engine
{
    export class texture2d: public texture
    {
    public:
        static auto create(u32 width, u32 height) -> texture2d*;
        static auto create(string_view file_path) -> texture2d*;
    };
}
