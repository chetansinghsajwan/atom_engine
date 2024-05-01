#include "renderer_2d.h"
#include "engine/opengl/opengl_shader.h"
#include "atom/engine/rendering/shader_factory.h"
#include "atom/engine/rendering/shader_registry.h"
#include "engine/rendering/render_command.h"
#include "atom/engine/logging.h"

namespace atom::engine
{
    static shader* _flat_color_shader;
    static vertex_array* _square_vertex_array;

    auto renderer_2d::initialize() -> void
    {
        ATOM_ENGINE_LOG_INFO("initializing renderer_2d...");

        shader_factory::set_root_path("/home/chetan/projects/atom.engine/sandbox");

        float vertices[] = { -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.5f,
            0.5f, 0.0f, 1.0f, 1.0f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f };

        uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };

        _square_vertex_array = vertex_array::create();

        vertex_buffer* square_vertex_buffer =
            vertex_buffer::create(vertices, sizeof(vertices) / sizeof(float));

        square_vertex_buffer->set_layout({
            { shader_data_type::float3, "a_position"      },
            { shader_data_type::float2, "a_texture_coord" }
        });

        _square_vertex_array->add_vertex_buffer(&*square_vertex_buffer);

        index_buffer* square_index_buffer =
            index_buffer::create(indices, sizeof(indices) / sizeof(uint32_t));

        _square_vertex_array->set_index_buffer(&*square_index_buffer);

        _flat_color_shader = shader_factory::create_from_file("assets/shaders/flat_color.glsl");

        shader_registry::register_("flat_color", &*_flat_color_shader).panic_on_error();

        ATOM_ENGINE_LOG_INFO("initializing renderer_2d done.");
    }

    auto renderer_2d::finalize() -> void
    {
        ATOM_ENGINE_LOG_INFO("finalizing renderer_2d...");

        render_command::finalize();

        delete _square_vertex_array;
        delete _flat_color_shader;

        ATOM_ENGINE_LOG_INFO("finalizing renderer_2d done.");
    }

    auto renderer_2d::begin_scene(orthographic_camera* camera) -> void
    {
        _flat_color_shader->bind();
        _flat_color_shader->set_uniform_mat4("u_transform", glm::mat4(1));
        _flat_color_shader->set_uniform_mat4("u_view_projection", camera->get_projection_matrix());
    }

    auto renderer_2d::end_scene() -> void {}

    auto renderer_2d::draw_quad(vec3 position, vec2 size, vec4 color) -> void
    {
        _flat_color_shader->bind();
        _flat_color_shader->set_uniform_float4("u_color", color);

        _square_vertex_array->bind();
        render_command::draw_indexed(_square_vertex_array);
    }
}
