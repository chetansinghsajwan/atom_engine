#pragma once
#include "engine/rendering/orthographic_camera.h"
#include "atom/engine/rendering/texture2d.h"

namespace atom::engine
{
    class renderer_2d
    {
    public:
        struct statistics
        {
            u32 draw_calls = 0;
            u32 quad_count = 0;

            auto get_total_vertex_count() -> u32
            {
                return quad_count * 4;
            }

            auto get_total_index_count() -> u32
            {
                return quad_count * 6;
            }
        };

    public:
        static auto initialize() -> void;
        static auto finalize() -> void;

        static auto begin_scene(orthographic_camera* camera) -> void;
        static auto end_scene() -> void;
        static auto flush() -> void;

        static auto draw_quad(vec3 position, vec2 size, float rotation, vec4 color) -> void;
        static auto draw_texture(vec3 position, vec2 size, float rotation, texture2d* texture,
            float tiling_factor, vec4 tint = vec4(1)) -> void;

        static auto reset_stats() -> void;
        static auto get_stats() -> statistics;

    private:
        static auto start_new_batch() -> void;
    };
}
