export module atom_engine:opengl.renderer_api;

import atom_core;
import :math;
import :rendering;

namespace atom::engine
{
    class opengl_renderer_api: public renderer_api
    {
    public:
        opengl_renderer_api();
        ~opengl_renderer_api();

    public:
        virtual auto initialize() -> void override;

        virtual auto finalize() -> void override;

        virtual auto set_clear_color(const class color& color) -> void override;

        virtual auto clear_color() -> void override;

        virtual auto draw_indexed(vertex_array* arr, u32 index_count = 0) -> void override;

        virtual auto set_viewport(u32 x, u32 y, u32 width, u32 height) -> void override;
    };
}
