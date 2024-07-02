export module atom.engine:rendering.renderer_api;

import atom_core;
import :math;
import :rendering.vertex_array;

namespace atom::engine
{
    class renderer_api
    {
    public:
        enum class api
        {
            none,
            opengl
        };

    public:
        static auto get_api() -> api
        {
            return _api;
        }

        virtual auto initialize() -> void = 0;
        virtual auto finalize() -> void = 0;
        virtual auto set_clear_color(const class color& color) -> void = 0;
        virtual auto clear_color() -> void = 0;
        virtual auto draw_indexed(vertex_array* arr, u32 index_count = 0) -> void = 0;
        virtual auto set_viewport(u32 x, u32 y, u32 width, u32 height) -> void = 0;

    private:
        static inline api _api = api::opengl;
    };
}
