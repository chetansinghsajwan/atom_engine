export module atom.engine:rendering.texture_factory;

import atom.core;
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

        static auto create_from_data(memory_view data, u32vec2 size) -> texture2d*;
    };
}
