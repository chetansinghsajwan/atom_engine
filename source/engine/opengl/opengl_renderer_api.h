#pragma once
#include "engine/rendering/renderer_api.h"

namespace atom::engine
{
    class opengl_renderer_api: public renderer_api
    {
    public:
        virtual auto initialize() -> void override;
        virtual auto finalize() -> void override;
        virtual auto set_clear_color(vec4 color) -> void override;
        virtual auto clear_color() -> void override;
        virtual auto draw_indexed(vertex_array* arr) -> void override;
        virtual auto set_viewport(u32 x, u32 y, u32 width, u32 height) -> void override;
    };
}
