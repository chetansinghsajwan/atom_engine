#include "atom.engine.h"
#include "engine/opengl/opengl_shader.h"
#include "engine/rendering/renderer.h"

using namespace atom;
using namespace atom::logging;
using namespace atom::engine;

class sandbox_layer: public layer
{
public:
    sandbox_layer()
        : layer("sandbox")
        , _camera(-1.6f, 1.6f, -0.9f, 0.9f) // ratio: 16:9
    {
        _vertex_array = std::unique_ptr<vertex_array>(vertex_array::create());

        // clang-format off
        float vertices[] =
        {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };
        // clang-format on

        vertex_buffer* vbuffer = vertex_buffer::create(vertices, sizeof(vertices) / sizeof(float));
        vbuffer->set_layout({
            {shader_data_type::float3,  "a_position"},
            { shader_data_type::float4, "a_color"   }
        });
        _vertex_array->add_vertex_buffer(&*vbuffer);

        uint32_t indices[3] = { 0, 1, 2 };
        index_buffer* ibuffer = index_buffer::create(indices, sizeof(indices) / sizeof(uint32_t));
        _vertex_array->set_index_buffer(&*ibuffer);

        const string_view vertex_shader_source = R"(
            #version 330 core

            layout(location = 0) in vec3 a_position;
            layout(location = 1) in vec4 a_color;

			out vec3 v_position;
			out vec4 v_color;

            uniform mat4 u_view_projection;

            void main()
            {
                v_position = a_position;
                v_color = a_color;
                gl_Position = u_view_projection * vec4(a_position, 1.0);
            }
        )";

        const string_view fragment_shader_source = R"(
            #version 330 core

            layout(location = 0) out vec4 color;
			in vec3 v_position;
			in vec4 v_color;

            void main()
            {
                color = v_color;
            }
        )";

        _shader = std::make_unique<opengl_shader>(vertex_shader_source, fragment_shader_source);
    }

    ~sandbox_layer()
    {
        delete _vertex_array->get_index_buffer();
        for (const vertex_buffer* buffer : _vertex_array->get_vertex_buffers())
        {
            delete buffer;
        }
    }

public:
    virtual auto on_update() -> void override
    {
        render_command::set_clear_color({ 0.1f, 0.1f, 0.1f, 1 });
        render_command::clear_color();

        _camera.set_position({ 0.5f, 0.5f, 0.0f });
        _camera.set_rotation(45.0f);

        renderer::begin_scene(&_camera);
        renderer::submit(&*_shader, &*_vertex_array);
        renderer::end_scene();
    }

private:
    std::unique_ptr<shader> _shader;
    std::unique_ptr<vertex_array> _vertex_array;
    orthographic_camera _camera;
};

class sandbox_application: public application
{
public:
    sandbox_application()
    {
        push_layer(&_layer);
    }

private:
    sandbox_layer _layer;
};

namespace atom::engine
{
    extern application* create_application()
    {
        return new sandbox_application();
    }
}
