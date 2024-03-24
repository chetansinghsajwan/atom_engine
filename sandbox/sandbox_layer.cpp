#include "sandbox_layer.h"
#include "atom/engine/rendering/shader_factory.h"
#include "engine/rendering/renderer.h"
#include "engine/opengl/opengl_shader.h"

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

        _checkerboard_texture->bind();
        renderer::submit(
            &*_texture_shader, &*_vertex_array, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        _cherno_texture->bind();
        renderer::submit(
            &*_texture_shader, &*_vertex_array, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

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
		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
        // clang-format on

        vertex_buffer* vbuffer = vertex_buffer::create(vertices, sizeof(vertices) / sizeof(float));
        vbuffer->set_layout({
            {shader_data_type::float3,  "a_position"     },
            { shader_data_type::float2, "a_texture_coord"}
        });
        _vertex_array->add_vertex_buffer(&*vbuffer);

        uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };
        index_buffer* ibuffer = index_buffer::create(indices, sizeof(indices) / sizeof(uint32_t));
        _vertex_array->set_index_buffer(&*ibuffer);

        const string_view vertex_shader_source = R"(
            #version 330 core

            layout(location = 0) in vec3 a_position;
            layout(location = 1) in vec2 a_texture_coord;

            uniform mat4 u_view_projection;
            uniform mat4 u_transform;

            out vec2 v_texture_coord;

            void main()
            {
                v_texture_coord = a_texture_coord;
                gl_Position = u_view_projection * u_transform * vec4(a_position, 1.0);
            }
        )";

        const string_view fragment_shader_source = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

			in vec2 v_texture_coord;

			uniform sampler2D u_texture;

            void main()
            {
                color = texture(u_texture, v_texture_coord);
            }
        )";

        _texture_shader = std::unique_ptr<shader>(
            shader_factory::create_from_source(vertex_shader_source, fragment_shader_source));

        _checkerboard_texture = std::shared_ptr<texture2d>(texture2d::create(
            "/home/chetan/projects/atom.engine/sandbox/assets/textures/checkerboard.png"));

        _cherno_texture = std::shared_ptr<texture2d>(texture2d::create(
            "/home/chetan/projects/atom.engine/sandbox/assets/textures/cherno.png"));

        static_cast<opengl_shader*>(&*_texture_shader)->bind();
        static_cast<opengl_shader*>(&*_texture_shader)->upload_uniform_int("u_texture", 0);
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
