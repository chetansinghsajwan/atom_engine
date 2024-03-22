#pragma once
#include "renderer_api.h"
#include "engine/rendering/render_command.h"

namespace atom::engine
{
    class renderer
    {
    public:
        static auto get_api() -> renderer_api::api
        {
            return renderer_api::get_api();
        }

        static auto begin_scene() -> void;
        static auto end_scene() -> void;
        static auto submit(vertex_array* arr) -> void;
    };
}
