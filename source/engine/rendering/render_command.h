#pragma once
#include "engine/rendering/renderer_api.h"

namespace atom::engine
{
    class render_command
    {
    public:
        static auto set_clear_color(vec4 color) -> void
        {
            _api->set_clear_color(color);
        }

        static auto clear_color() -> void
        {
            _api->clear_color();
        }

        static auto draw_indexed(vertex_array* arr) -> void
        {
            _api->draw_indexed(arr);
        }

    private:
        static renderer_api* _api;
    };
}
