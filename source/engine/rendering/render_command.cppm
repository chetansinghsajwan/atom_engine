export module atom.engine:rendering.render_command;

import atom.core;
import :math;
import :rendering.renderer_api;
import :rendering.vertex_array;

namespace atom::engine
{
    // @todo: remove this export.
    export class render_command
    {
    public:
        static auto initialize() -> void
        {
            _api->initialize();
        }

        static auto finalize() -> void
        {
            _api->finalize();
        }

        static auto set_viewport(u32 x, u32 y, u32 width, u32 height) -> void
        {
            _api->set_viewport(x, y, width, height);
        }

        static auto set_clear_color(const class color& color) -> void
        {
            _api->set_clear_color(color);
        }

        static auto clear_color() -> void
        {
            _api->clear_color();
        }

        static auto draw_indexed(vertex_array* arr, u32 index_count = 0) -> void
        {
            _api->draw_indexed(arr, index_count);
        }

    private:
        static renderer_api* _api;
    };
}
