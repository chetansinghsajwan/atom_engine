export module atom.engine:rendering.renderer_2d;

import atom.core;
import atom.logging;
import :math;
import :colors;
import :logging;
import :rendering.orthographic_camera;
import :rendering.texture2d;

namespace atom::engine
{
    // @todo: remove this export.
    export class renderer_2d
    {
    public:
        struct statistics
        {
            statistics()
                : draw_calls{ 0 }
                , quad_count{ 0 }
            {}

            auto get_total_vertex_count() -> u32
            {
                return quad_count * 4;
            }

            auto get_total_index_count() -> u32
            {
                return quad_count * 6;
            }

            u32 draw_calls;
            u32 quad_count;
        };

    public:
        static auto initialize() -> void;

        static auto finalize() -> void;

        static auto begin_scene(orthographic_camera* camera) -> void;

        static auto begin_scene(class camera* camera, const f32mat4& transform) -> void;

        static auto end_scene() -> void;

        static auto flush() -> void;

        static auto draw_quad(const f32mat4& transform, const class color& color) -> void;

        static auto draw_quad(
            const f32vec3& position, f32vec2 size, f32 rotation, const class color& color) -> void;

        static auto draw_texture(const f32mat4& transform, texture2d* texture, f32 tiling_factor,
            const class color& tint) -> void;

        static auto draw_texture(const f32vec3& position, f32vec2 size, f32 rotation,
            texture2d* texture, f32 tiling_factor, const class color& tint) -> void;

        static auto draw_sprite(const f32vec3& position, f32vec2 size, f32 rotation,
            class sprite* sprite, f32 tiling_factor, const class color& tint) -> void;

        static auto draw_sprite(const f32mat4& transform, class sprite* sprite, f32 tiling_factor,
            const class color& tint) -> void;

        static auto reset_stats() -> void;

        static auto get_stats() -> statistics;

    private:
        static auto _draw(const f32mat4& transform, texture2d* texture,
            const f32vec2* texture_coords, f32 tiling_factor, const class color& tint) -> void;

        static auto _draw(const f32vec3& position, f32vec2 size, f32 rotation, texture2d* texture,
            const f32vec2* texture_coords, f32 tiling_factor, const class color& tint) -> void;

        static auto _start_new_batch() -> void;

        static auto _get_texture_index(texture2d* texture) -> usize;

    public:
        static inline string_view assets_path = "";
    };
}
