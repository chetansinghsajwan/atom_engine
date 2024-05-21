export module atom.engine:rendering.renderer_2d;

import atom.core;
import :math;
import :colors;
import :logging;
import :rendering.orthographic_camera;
import :rendering.shader_factory;
import :rendering.render_command;
import :rendering.camera;
import :rendering.sprite;
import :rendering.texture2d;
import :rendering.frame_buffer;
import :rendering.vertex_array;

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

    private:
        struct _quad_vertex
        {
            vec3 position;
            class color color;
            vec2 texture_coord;
            float texture_index;
            float tiling_factor;
        };

    public:
        static auto initialize() -> void
        {
            ATOM_ENGINE_LOG_INFO("initializing renderer_2d...");

            shader_factory::set_root_path(
                "/home/chetan/projects/atom-workspace/atom.engine/sandbox");

            _quad_vertex_array = vertex_array::create();

            _quad_vertex_buffer =
                vertex_buffer::create_with_size(_max_vertices * sizeof(_quad_vertex));
            _quad_vertex_buffer->set_layout({
                { shader_data_type::float3, "a_position"      },
                { shader_data_type::float4, "a_color"         },
                { shader_data_type::float2, "a_texture_coord" },
                { shader_data_type::float1, "a_texture_index" },
                { shader_data_type::float1, "a_tiling_factor" },
            });
            _quad_vertex_array->add_vertex_buffer(_quad_vertex_buffer);

            _quad_vertex_buffer_base = new _quad_vertex[_max_vertices];

            uint32_t* quad_indices = new uint32_t[_max_indices];
            u32 offset = 0;
            for (u32 i = 0; i < _max_indices; i += 6)
            {
                quad_indices[i + 0] = offset + 0;
                quad_indices[i + 1] = offset + 1;
                quad_indices[i + 2] = offset + 2;

                quad_indices[i + 3] = offset + 2;
                quad_indices[i + 4] = offset + 3;
                quad_indices[i + 5] = offset + 0;

                offset += 4;
            }

            index_buffer* quad_index_buffer = index_buffer::create(quad_indices, _max_indices);
            _quad_vertex_array->set_index_buffer(quad_index_buffer);
            delete[] quad_indices;

            int samplers[_max_texture_slots];
            for (usize i = 0; i < _max_texture_slots; i++)
                samplers[i] = i;

            _texture_shader = shader_factory::create_from_file("assets/shaders/texture.glsl");
            _texture_shader->bind();
            _texture_shader->set_int_array("u_textures", samplers, _max_texture_slots);

            _white_texture = texture2d::create(1, 1);
            u32 _white_texture_data = 0xffffffff;
            _white_texture->set_data(&_white_texture_data, sizeof(_white_texture_data));

            _texture_slots = new texture2d*[_max_texture_slots];
            _texture_slots[0] = _white_texture;

            _quad_vertex_positions[0] = vec4(-.5f, -.5f, 0, 1);
            _quad_vertex_positions[1] = vec4(.5f, -.5f, 0, 1);
            _quad_vertex_positions[2] = vec4(.5f, .5f, 0, 1);
            _quad_vertex_positions[3] = vec4(-.5f, .5f, 0, 1);

            ATOM_ENGINE_LOG_INFO("initializing renderer_2d done.");
        }

        static auto finalize() -> void
        {
            ATOM_ENGINE_LOG_INFO("finalizing renderer_2d...");

            render_command::finalize();

            delete _quad_vertex_array;
            delete _quad_vertex_buffer;
            delete _quad_vertex_buffer_base;
            delete _texture_shader;
            delete _texture_slots;

            ATOM_ENGINE_LOG_INFO("finalizing renderer_2d done.");
        }

        static auto begin_scene(orthographic_camera* camera) -> void
        {
            _texture_shader->bind();
            _texture_shader->set_uniform_mat4(
                "u_view_projection", camera->get_view_projection_matrix());

            _quad_vertex_buffer_ptr = _quad_vertex_buffer_base;
            _quad_index_count = 0;

            _texture_slot_index = 1;
        }

        static auto begin_scene(class camera* camera, const mat4& transform) -> void
        {
            mat4 view_projection = camera->get_projection() * math::inverse(transform);

            _texture_shader->bind();
            _texture_shader->set_uniform_mat4("u_view_projection", view_projection);

            _quad_vertex_buffer_ptr = _quad_vertex_buffer_base;
            _quad_index_count = 0;

            _texture_slot_index = 1;
        }

        static auto end_scene() -> void
        {
            u32 data_size = (uint8_t*)_quad_vertex_buffer_ptr - (uint8_t*)_quad_vertex_buffer_base;
            _quad_vertex_buffer->set_data(_quad_vertex_buffer_base, data_size);

            flush();
        }

        static auto flush() -> void
        {
            for (usize i = 0; i < _texture_slot_index; i++)
            {
                _texture_slots[i]->bind(i);
            }

            render_command::draw_indexed(_quad_vertex_array, _quad_index_count);
            _stats.draw_calls += 1;
        }

        static auto draw_quad(const mat4& transform, const class color& color) -> void
        {
            constexpr vec2 texture_coords[4] = { vec2(0, 0), vec2(1, 0), vec2(1, 1), vec2(0, 1) };

            _draw(transform, _white_texture, texture_coords, 1, color);
        }

        static auto draw_quad(
            const vec3& position, vec2 size, float rotation, const class color& color) -> void
        {
            constexpr vec2 texture_coords[4] = { vec2(0, 0), vec2(1, 0), vec2(1, 1), vec2(0, 1) };

            _draw(position, size, rotation, _white_texture, texture_coords, 1, color);
        }

        static auto draw_texture(const mat4& transform, texture2d* texture, float tiling_factor,
            const class color& tint) -> void
        {
            constexpr vec2 texture_coords[4] = { vec2(0, 0), vec2(1, 0), vec2(1, 1), vec2(0, 1) };

            _draw(transform, texture, texture_coords, tiling_factor, tint);
        }

        static auto draw_texture(const vec3& position, vec2 size, float rotation,
            texture2d* texture, float tiling_factor, const class color& tint) -> void
        {
            constexpr vec2 texture_coords[4] = { vec2(0, 0), vec2(1, 0), vec2(1, 1), vec2(0, 1) };

            _draw(position, size, rotation, texture, texture_coords, tiling_factor, tint);
        }

        static auto draw_sprite(const vec3& position, vec2 size, float rotation,
            class sprite* sprite, float tiling_factor, const class color& tint) -> void
        {
            _draw(position, size, rotation, sprite->get_texture(),
                sprite->get_texture_coords().get_data(), tiling_factor, tint);
        }

        static auto draw_sprite(const mat4& transform, class sprite* sprite, float tiling_factor,
            const class color& tint) -> void
        {
            _draw(transform, sprite->get_texture(), sprite->get_texture_coords().get_data(),
                tiling_factor, tint);
        }

        static auto reset_stats() -> void
        {
            _stats = renderer_2d::statistics();
        }

        static auto get_stats() -> statistics
        {
            return _stats;
        }

    private:
        static auto _draw(const mat4& transform, texture2d* texture, const vec2* texture_coords,
            float tiling_factor, const class color& tint) -> void
        {
            contract_debug_expects(texture != nullptr);

            if (_quad_index_count >= _max_indices)
            {
                _start_new_batch();
            }

            float texture_index = _get_texture_index(texture);

            _quad_vertex_buffer_ptr->position = transform * _quad_vertex_positions[0];
            _quad_vertex_buffer_ptr->color = tint;
            _quad_vertex_buffer_ptr->texture_coord = texture_coords[0];
            _quad_vertex_buffer_ptr->texture_index = texture_index;
            _quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
            _quad_vertex_buffer_ptr++;

            _quad_vertex_buffer_ptr->position = transform * _quad_vertex_positions[1];
            _quad_vertex_buffer_ptr->color = tint;
            _quad_vertex_buffer_ptr->texture_coord = texture_coords[1];
            _quad_vertex_buffer_ptr->texture_index = texture_index;
            _quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
            _quad_vertex_buffer_ptr++;

            _quad_vertex_buffer_ptr->position = transform * _quad_vertex_positions[2];
            _quad_vertex_buffer_ptr->color = tint;
            _quad_vertex_buffer_ptr->texture_coord = texture_coords[2];
            _quad_vertex_buffer_ptr->texture_index = texture_index;
            _quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
            _quad_vertex_buffer_ptr++;

            _quad_vertex_buffer_ptr->position = transform * _quad_vertex_positions[3];
            _quad_vertex_buffer_ptr->color = tint;
            _quad_vertex_buffer_ptr->texture_coord = texture_coords[3];
            _quad_vertex_buffer_ptr->texture_index = texture_index;
            _quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
            _quad_vertex_buffer_ptr++;

            _quad_index_count += 6;

            _stats.quad_count += 1;
        }

        static auto _draw(const vec3& position, vec2 size, float rotation, texture2d* texture,
            const vec2* texture_coords, float tiling_factor, const class color& tint) -> void
        {
            contract_debug_expects(texture != nullptr);

            mat4 transform =
                math::translate(mat4(1), position) * math::scale(mat4(1), vec3(size.x, size.y, 1));

            if (rotation != 0.)
            {
                transform *= math::rotate(mat4(1.0f), math::radians(rotation), vec3(0, 0, 1));
            }

            _draw(transform, texture, texture_coords, tiling_factor, tint);
        }

        static auto _start_new_batch() -> void
        {
            _quad_vertex_buffer_ptr = _quad_vertex_buffer_base;
            _quad_index_count = 0;

            _texture_slot_index = 1;

            renderer_2d::end_scene();
        }

        static auto _get_texture_index(texture2d* texture) -> usize
        {
            for (usize i = 0; i < _texture_slot_index; i++)
            {
                if (_texture_slots[i] == texture)
                    return i;
            }

            _texture_slots[_texture_slot_index] = texture;
            return _texture_slot_index++;
        }

    private:
        static constexpr u32 _max_quads = 10000;
        static constexpr u32 _max_vertices = _max_quads * 4;
        static constexpr u32 _max_indices = _max_quads * 6;
        static constexpr u32 _max_texture_slots = 32;
        static inline vertex_array* _quad_vertex_array = nullptr;
        static inline vertex_buffer* _quad_vertex_buffer = nullptr;
        static inline vec4 _quad_vertex_positions[4];
        static inline u32 _quad_index_count = 0;
        static inline shader* _texture_shader = nullptr;
        static inline _quad_vertex* _quad_vertex_buffer_base = nullptr;
        static inline _quad_vertex* _quad_vertex_buffer_ptr = nullptr;
        static inline texture2d* _white_texture = nullptr;
        static inline texture2d** _texture_slots;
        static inline u32 _texture_slot_index = 1; // 0 is reserved for white
        static inline renderer_2d::statistics _stats;
    };
}
