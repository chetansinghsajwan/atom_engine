module atom.engine:rendering.renderer_2d.impl;

import :rendering.renderer_2d;
import atom.core;
import atom.logging;
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
    struct _quad_vertex
    {
        f32vec3 position;
        class color color;
        f32vec2 texture_coord;
        f32 texture_index;
        f32 tiling_factor;
    };

    logging::logger* _logger = nullptr;

    constexpr u32 _max_quads = 10000;
    constexpr u32 _max_vertices = _max_quads * 4;
    constexpr u32 _max_indices = _max_quads * 6;
    constexpr u32 _max_texture_slots = 32;
    vertex_array* _quad_vertex_array = nullptr;
    vertex_buffer* _quad_vertex_buffer = nullptr;
    f32vec4 _quad_vertex_positions[4];
    u32 _quad_index_count = 0;
    shader* _texture_shader = nullptr;
    _quad_vertex* _quad_vertex_buffer_base = nullptr;
    _quad_vertex* _quad_vertex_buffer_ptr = nullptr;
    texture2d* _white_texture = nullptr;
    texture2d** _texture_slots;
    u32 _texture_slot_index = 1; // 0 is reserved for white
    renderer_2d::statistics _stats;

    auto renderer_2d::initialize() -> void
    {
        _logger = logging::logger_manager::create_logger({ .name = "renderer_2d" }).get_value();

        _logger->log_info("initializing renderer_2d...");

        shader_factory::set_root_path(assets_path);

        _quad_vertex_array = vertex_array::create();

        _quad_vertex_buffer = vertex_buffer::create_with_size(_max_vertices * sizeof(_quad_vertex));
        _quad_vertex_buffer->set_layout({
            { shader_data_type::float3, "a_position"      },
            { shader_data_type::float4, "a_color"         },
            { shader_data_type::float2, "a_texture_coord" },
            { shader_data_type::float1, "a_texture_index" },
            { shader_data_type::float1, "a_tiling_factor" },
        });
        _quad_vertex_array->add_vertex_buffer(_quad_vertex_buffer);

        _quad_vertex_buffer_base = new _quad_vertex[_max_vertices];

        u32* quad_indices = new u32[_max_indices];
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

        _texture_shader = shader_factory::create_from_files("shaders/basic").get_value();
        _texture_shader->bind();
        _texture_shader->set_int_array("u_textures", samplers, _max_texture_slots);

        _white_texture = texture2d::create(1, 1);
        u32 _white_texture_data = 0xffffffff;
        _white_texture->set_data(&_white_texture_data, sizeof(_white_texture_data));

        _texture_slots = new texture2d*[_max_texture_slots];
        _texture_slots[0] = _white_texture;

        _quad_vertex_positions[0] = f32vec4(-.5f, -.5f, 0, 1);
        _quad_vertex_positions[1] = f32vec4(.5f, -.5f, 0, 1);
        _quad_vertex_positions[2] = f32vec4(.5f, .5f, 0, 1);
        _quad_vertex_positions[3] = f32vec4(-.5f, .5f, 0, 1);

        _logger->log_info("initializing renderer_2d done.");
    }

    auto renderer_2d::finalize() -> void
    {
        _logger->log_info("finalizing renderer_2d...");

        render_command::finalize();

        delete _quad_vertex_array;
        delete _quad_vertex_buffer;
        delete _quad_vertex_buffer_base;
        delete _texture_shader;
        delete _texture_slots;

        _logger->log_info("finalizing renderer_2d done.");
    }

    auto renderer_2d::begin_scene(orthographic_camera* camera) -> void
    {
        _texture_shader->bind();
        _texture_shader->set_uniform_mat4(
            "u_view_projection", camera->get_view_projection_matrix());

        _quad_vertex_buffer_ptr = _quad_vertex_buffer_base;
        _quad_index_count = 0;

        _texture_slot_index = 1;
    }

    auto renderer_2d::begin_scene(class camera* camera, const f32mat4& transform) -> void
    {
        f32mat4 view_projection = camera->get_projection() * math::inverse(transform);

        _texture_shader->bind();
        _texture_shader->set_uniform_mat4("u_view_projection", view_projection);

        _quad_vertex_buffer_ptr = _quad_vertex_buffer_base;
        _quad_index_count = 0;

        _texture_slot_index = 1;
    }

    auto renderer_2d::end_scene() -> void
    {
        u32 data_size = (u8*)_quad_vertex_buffer_ptr - (u8*)_quad_vertex_buffer_base;
        _quad_vertex_buffer->set_data(_quad_vertex_buffer_base, data_size);

        flush();
    }

    auto renderer_2d::flush() -> void
    {
        for (usize i = 0; i < _texture_slot_index; i++)
        {
            _texture_slots[i]->bind(i);
        }

        render_command::draw_indexed(_quad_vertex_array, _quad_index_count);
        _stats.draw_calls += 1;
    }

    auto renderer_2d::draw_quad(const f32mat4& transform, const class color& color) -> void
    {
        constexpr f32vec2 texture_coords[4] = {
            f32vec2{ 0, 0 },
            f32vec2{ 1, 0 },
            f32vec2{ 1, 1 },
            f32vec2{ 0, 1 },
        };

        _draw(transform, _white_texture, texture_coords, 1, color);
    }

    auto renderer_2d::draw_quad(
        const f32vec3& position, f32vec2 size, f32 rotation, const class color& color) -> void
    {
        constexpr f32vec2 texture_coords[4] = {
            f32vec2{ 0, 0 },
            f32vec2{ 1, 0 },
            f32vec2{ 1, 1 },
            f32vec2{ 0, 1 },
        };

        _draw(position, size, rotation, _white_texture, texture_coords, 1, color);
    }

    auto renderer_2d::draw_texture(const f32mat4& transform, texture2d* texture, f32 tiling_factor,
        const class color& tint) -> void
    {
        constexpr f32vec2 texture_coords[4] = {
            f32vec2{ 0, 0 },
            f32vec2{ 1, 0 },
            f32vec2{ 1, 1 },
            f32vec2{ 0, 1 },
        };

        _draw(transform, texture, texture_coords, tiling_factor, tint);
    }

    auto renderer_2d::draw_texture(const f32vec3& position, f32vec2 size, f32 rotation,
        texture2d* texture, f32 tiling_factor, const class color& tint) -> void
    {
        constexpr f32vec2 texture_coords[4] = {
            f32vec2{ 0, 0 },
            f32vec2{ 1, 0 },
            f32vec2{ 1, 1 },
            f32vec2{ 0, 1 },
        };

        _draw(position, size, rotation, texture, texture_coords, tiling_factor, tint);
    }

    auto renderer_2d::draw_sprite(const f32vec3& position, f32vec2 size, f32 rotation,
        class sprite* sprite, f32 tiling_factor, const class color& tint) -> void
    {
        _draw(position, size, rotation, sprite->get_texture(),
            sprite->get_texture_coords().get_data(), tiling_factor, tint);
    }

    auto renderer_2d::draw_sprite(const f32mat4& transform, class sprite* sprite, f32 tiling_factor,
        const class color& tint) -> void
    {
        _draw(transform, sprite->get_texture(), sprite->get_texture_coords().get_data(),
            tiling_factor, tint);
    }

    auto renderer_2d::reset_stats() -> void
    {
        _stats = renderer_2d::statistics();
    }

    auto renderer_2d::get_stats() -> statistics
    {
        return _stats;
    }

    auto renderer_2d::_draw(const f32mat4& transform, texture2d* texture,
        const f32vec2* texture_coords, f32 tiling_factor, const class color& tint) -> void
    {
        contract_debug_expects(texture != nullptr);

        if (_quad_index_count >= _max_indices)
        {
            _start_new_batch();
        }

        f32 texture_index = _get_texture_index(texture);

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

    auto renderer_2d::_draw(const f32vec3& position, f32vec2 size, f32 rotation, texture2d* texture,
        const f32vec2* texture_coords, f32 tiling_factor, const class color& tint) -> void
    {
        contract_debug_expects(texture != nullptr);

        f32mat4 transform = math::translate(f32mat4{ 1 }, position)
                            * math::scale(f32mat4{ 1 }, f32vec3{ size.x, size.y, 1 });

        if (rotation != 0.)
        {
            transform *= math::rotate(f32mat4{ 1 }, math::radians(rotation), f32vec3{ 0, 0, 1 });
        }

        _draw(transform, texture, texture_coords, tiling_factor, tint);
    }

    auto renderer_2d::_start_new_batch() -> void
    {
        _quad_vertex_buffer_ptr = _quad_vertex_buffer_base;
        _quad_index_count = 0;

        _texture_slot_index = 1;

        renderer_2d::end_scene();
    }

    auto renderer_2d::_get_texture_index(texture2d* texture) -> usize
    {
        for (usize i = 0; i < _texture_slot_index; i++)
        {
            if (_texture_slots[i] == texture)
                return i;
        }

        _texture_slots[_texture_slot_index] = texture;
        return _texture_slot_index++;
    }
}
