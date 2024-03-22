#include "sandbox_layer.h"
#include "engine/opengl/opengl_shader.h"
#include "engine/rendering/renderer.h"

using namespace atom;
using namespace atom::logging;
using namespace atom::engine;

namespace sandbox
{
    sandbox_layer::sandbox_layer()
        : layer("sandbox")
        , _camera(-1.6f, 1.6f, -0.9f, 0.9f) // ratio: 16:9
        , _camera_pos(0, 0, 0)
        , _camera_rot(0)
        , _camera_move_speed(3)
        , _camera_rot_speed(140)
    {
        _setup_logging();
        _setup_keyboard();
        _setup_rendering();
    }

    sandbox_layer::~sandbox_layer()
    {
        delete _vertex_array->get_index_buffer();
        for (const vertex_buffer* buffer : _vertex_array->get_vertex_buffers())
        {
            delete buffer;
        }
    }

    auto sandbox_layer::on_attach() -> void
    {
        _logger->log_info("sandbox layer attached.");
    }

    auto sandbox_layer::on_update(time_stemp delta_time) -> void
    {
        _process_inputs(delta_time);

        _camera.set_position(_camera_pos);
        _camera.set_rotation(_camera_rot);

        render_command::set_clear_color({ 0.1f, 0.1f, 0.1f, 1 });
        render_command::clear_color();

        renderer::begin_scene(&_camera);
        renderer::submit(&*_shader, &*_vertex_array);
        renderer::end_scene();
    }

    auto sandbox_layer::_setup_logging() -> void
    {
        _logger = logger_manager::create_logger({ .name = "sandbox" }).get_at<0>();
    }

    auto sandbox_layer::_setup_keyboard() -> void
    {
        for (input_device* device : input_manager::get_devices())
        {
            if (device->get_type() == input_device_type::keyboard)
            {
                _keyboard = reinterpret_cast<keyboard*>(device);
                _logger->log_info("using keyboard '{}'.", _keyboard->get_name());
                break;
            }
        }

        ATOM_DEBUG_ASSERTS(_keyboard != nullptr);
    }

    auto sandbox_layer::_setup_rendering() -> void
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

    auto sandbox_layer::_process_inputs(time_stemp delta_time) -> void
    {
        ATOM_DEBUG_EXPECTS(_keyboard != nullptr);

        if (_keyboard->is_key_down(keyboard_key_code::w))
        {
            _camera_pos.y += _camera_move_speed * delta_time.get_seconds();
        }

        if (_keyboard->is_key_down(keyboard_key_code::s))
        {
            _camera_pos.y -= _camera_move_speed * delta_time.get_seconds();
        }

        if (_keyboard->is_key_down(keyboard_key_code::a))
        {
            _camera_pos.x -= _camera_move_speed * delta_time.get_seconds();
        }

        if (_keyboard->is_key_down(keyboard_key_code::d))
        {
            _camera_pos.x += _camera_move_speed * delta_time.get_seconds();
        }

        if (_keyboard->is_key_down(keyboard_key_code::q))
        {
            _camera_pos.z -= _camera_move_speed * delta_time.get_seconds();
        }

        if (_keyboard->is_key_down(keyboard_key_code::e))
        {
            _camera_pos.z += _camera_move_speed * delta_time.get_seconds();
        }

        if (_keyboard->is_key_down(keyboard_key_code::z))
        {
            _camera_rot += _camera_rot_speed * delta_time.get_seconds();
        }

        if (_keyboard->is_key_down(keyboard_key_code::x))
        {
            _camera_rot -= _camera_rot_speed * delta_time.get_seconds();
        }
    }
}
