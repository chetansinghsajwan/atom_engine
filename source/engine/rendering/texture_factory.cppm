export module atom_engine:rendering.texture_factory;

import atom_core;
import :rendering.texture;
import :rendering.texture2d;
import :math;

namespace atom::engine
{
    export class texture_factory
    {
    public:
        static auto create_from_file(
            string_view file_path) -> result<texture2d*, runtime_error,
                                       filesystem::filesystem_error, filesystem::noentry_error>;

        static auto create_from_data(
            memory_view data, texture_format format, u32vec2 size) -> texture2d*;
    };
}
