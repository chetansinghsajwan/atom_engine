#include "renderer_2d.h"
#include "engine/opengl/opengl_shader.h"
#include "atom/engine/rendering/shader_factory.h"
#include "engine/rendering/render_command.h"
#include "atom/engine/math.h"
#include "atom/engine/logging.h"

namespace atom::engine
{
    struct quad_vertex
    {
        vec3 position;
        vec4 color;
        vec2 texture_coord;
    };

    static const u32 _max_quads = 10000;
    static const u32 _max_vertices = _max_quads * 4;
    static const u32 _max_indices = _max_quads * 6;
    static vertex_array* _quad_vertex_array = nullptr;
    static vertex_buffer* _quad_vertex_buffer = nullptr;
    static shader* _texture_shader = nullptr;
    static texture2d* _white_texture = nullptr;
    static u32 _quad_index_count = 0;
    static quad_vertex* _quad_vertex_buffer_base = nullptr;
    static quad_vertex* _quad_vertex_buffer_ptr = nullptr;

    auto renderer_2d::initialize() -> void
    {
        ATOM_ENGINE_LOG_INFO("initializing renderer_2d...");

        shader_factory::set_root_path("/home/chetan/projects/atom.engine/sandbox");

        // float vertices[] = { -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.5f,
        //     0.5f, 0.0f, 1.0f, 1.0f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f };

        _quad_vertex_array = vertex_array::create();

        _quad_vertex_buffer = vertex_buffer::create_with_size(_max_vertices * sizeof(quad_vertex));
        _quad_vertex_buffer->set_layout({
            { shader_data_type::float3, "a_position"      },
            { shader_data_type::float4, "a_color"         },
            { shader_data_type::float2, "a_texture_coord" }
        });
        _quad_vertex_array->add_vertex_buffer(_quad_vertex_buffer);

        _quad_vertex_buffer_base = new quad_vertex[_max_vertices];

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
        delete quad_indices;

        _texture_shader = shader_factory::create_from_file("assets/shaders/texture.glsl");
        _texture_shader->bind();
        // _texture_shader->set_uniform_int("u_texture", 0);

        _white_texture = texture2d::create(1, 1);
        u32 _white_texture_data = 0xffffffff;
        _white_texture->set_data(&_white_texture_data, sizeof(_white_texture_data));

        ATOM_ENGINE_LOG_INFO("initializing renderer_2d done.");
    }

    auto renderer_2d::finalize() -> void
    {
        ATOM_ENGINE_LOG_INFO("finalizing renderer_2d...");

        render_command::finalize();

        delete _quad_vertex_array;
        delete _quad_vertex_buffer;
        delete _quad_vertex_buffer_base;
        delete _texture_shader;

        ATOM_ENGINE_LOG_INFO("finalizing renderer_2d done.");
    }

    auto renderer_2d::begin_scene(orthographic_camera* camera) -> void
    {
        _texture_shader->bind();
        _texture_shader->set_uniform_mat4(
            "u_view_projection", camera->get_view_projection_matrix());

        _quad_vertex_buffer_ptr = _quad_vertex_buffer_base;
        _quad_index_count = 0;
    }

    auto renderer_2d::end_scene() -> void
    {
        u32 data_size = (uint8_t*)_quad_vertex_buffer_ptr - (uint8_t*)_quad_vertex_buffer_base;
        _quad_vertex_buffer->set_data(_quad_vertex_buffer_base, data_size);

        flush();
    }

    auto renderer_2d::flush() -> void
    {
        render_command::draw_indexed(_quad_vertex_array, _quad_index_count);
    }

    auto renderer_2d::draw_quad(vec3 position, vec2 size, float rotation, vec4 color) -> void
    {
        _quad_vertex_buffer_ptr->position = position;
        _quad_vertex_buffer_ptr->color = color;
        _quad_vertex_buffer_ptr->texture_coord = vec2(0, 0);
        _quad_vertex_buffer_ptr++;

        _quad_vertex_buffer_ptr->position = vec3(position.x + size.x, position.y, 0);
        _quad_vertex_buffer_ptr->color = color;
        _quad_vertex_buffer_ptr->texture_coord = vec2(1, 0);
        _quad_vertex_buffer_ptr++;

        _quad_vertex_buffer_ptr->position = vec3(position.x + size.x, position.y + size.x, 0);
        _quad_vertex_buffer_ptr->color = color;
        _quad_vertex_buffer_ptr->texture_coord = vec2(1, 1);
        _quad_vertex_buffer_ptr++;

        _quad_vertex_buffer_ptr->position = vec3(position.x, position.y + size.y, 0);
        _quad_vertex_buffer_ptr->color = color;
        _quad_vertex_buffer_ptr->texture_coord = vec2(0, 1);
        _quad_vertex_buffer_ptr++;

        _quad_index_count += 6;

        // mat4 transform = math::translate(mat4(1), position) * math::scale(mat4(1), vec3(size, 1));

        // if (rotation != 0)
        // {
        //     transform *= math::rotate(mat4(1), rotation, vec3(0, 0, 1));
        // }

        // _texture_shader->set_uniform_mat4("u_transform", transform);
        // _texture_shader->set_uniform_float("u_tiling_factor", 1);
        // _texture_shader->set_uniform_float4("u_color", color);

        // _white_texture->bind();
        // _quad_vertex_array->bind();
        // render_command::draw_indexed(_quad_vertex_array);
    }

    auto renderer_2d::draw_texture(vec3 position, vec2 size, float rotation, texture2d* texture,
        float tiling_factor, vec4 tint) -> void
    {
        mat4 transform = math::translate(mat4(1), position) * math::scale(mat4(1), vec3(size, 1));

        if (rotation != 0)
        {
            transform *= math::rotate(mat4(1), rotation, vec3(0, 0, 1));
        }

        _texture_shader->set_uniform_mat4("u_transform", transform);
        _texture_shader->set_uniform_float("u_tiling_factor", tiling_factor);
        _texture_shader->set_uniform_float4("u_color", tint);

        texture->bind();
        _quad_vertex_array->bind();
        render_command::draw_indexed(_quad_vertex_array);
    }
}
