#pragma once
#include "atom/engine/math.h"
#include "engine/rendering/vertex_array.h"

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
        virtual auto set_clear_color(vec4 color) -> void = 0;
        virtual auto clear_color() -> void = 0;
        virtual auto draw_indexed(vertex_array* arr) -> void = 0;
        virtual auto set_viewport(u32 x, u32 y, u32 width, u32 height) -> void = 0;

    private:
        static api _api;
    };
}
