#include "sandbox_layer_2d.h"
#include "atom/engine/rendering/shader_factory.h"
#include "atom/engine/rendering/shader_registry.h"
#include "atom/engine/window/window_manager.h"
#include "engine/rendering/renderer.h"
#include "engine/opengl/opengl_shader.h"
#include "imgui.h"

using namespace atom;
using namespace atom::logging;
using namespace atom::engine;

namespace sandbox
{
    sandbox_layer_2d::sandbox_layer_2d()
        : layer("sandbox")
        , _camera_controller(1920.0 / 1080.0)
        , _square_color(.2f, .3f, .8f, 1)
    {
        _setup_logging();
    }

    sandbox_layer_2d::~sandbox_layer_2d()
    {
        delete _square_vertex_array->get_index_buffer();
        for (const vertex_buffer* buffer : _square_vertex_array->get_vertex_buffers())
        {
            delete buffer;
        }
    }

    auto sandbox_layer_2d::on_attach() -> void
    {
        _logger->log_info("sandbox_layer_2d attached.");

        _setup_window();
        _setup_keyboard();
        _setup_mouse();
        _setup_rendering();

        _camera_controller.set_window(_window);
        _camera_controller.set_keyboard(_keyboard);
        _camera_controller.set_mouse(_mouse);
    }

    auto sandbox_layer_2d::on_update(time_stemp delta_time) -> void
    {
        _camera_controller.on_update(delta_time);

        render_command::set_clear_color({ 0.1f, 0.1f, 0.1f, 1 });
        render_command::clear_color();

        renderer::begin_scene(_camera_controller.get_camera());

        opengl_shader* opengl_flat_color_shader = reinterpret_cast<opengl_shader*>(&*_flat_color_shader);
        opengl_flat_color_shader->bind();
        opengl_flat_color_shader->upload_uniform_float4("u_color", _square_color);

        renderer::submit(
            &*_flat_color_shader, &*_square_vertex_array, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        renderer::end_scene();
    }

    auto sandbox_layer_2d::on_imgui_render() -> void
    {
        ImGui::Begin("settings");
        ImGui::ColorEdit4("square color", glm::value_ptr(_square_color));
        ImGui::End();
    }

    auto sandbox_layer_2d::_setup_logging() -> void
    {
        _logger = logger_manager::create_logger({ .name = "sandbox" }).get_value();
    }

    auto sandbox_layer_2d::_setup_window() -> void
    {
        _window = window_manager::get_windows().get_mut_front();
        _logger->log_info("using window '{}'.", _window->get_name());

        ATOM_DEBUG_ASSERTS(_window != nullptr);
    }

    auto sandbox_layer_2d::_setup_keyboard() -> void
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

    auto sandbox_layer_2d::_setup_mouse() -> void
    {
        for (input_device* device : input_manager::get_devices())
        {
            if (device->get_type() == input_device_type::mouse)
            {
                _mouse = reinterpret_cast<mouse*>(device);
                _logger->log_info("using mouse '{}'.", _mouse->get_name());
                break;
            }
        }

        ATOM_DEBUG_ASSERTS(_mouse != nullptr);
    }

    auto sandbox_layer_2d::_setup_rendering() -> void
    {
        shader_factory::set_root_path("/home/chetan/projects/atom.engine/sandbox");

        float vertices[] = { -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.5f,
            0.5f, 0.0f, 1.0f, 1.0f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f };

        uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };

        _square_vertex_array = std::unique_ptr<vertex_array>(vertex_array::create());

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

        _flat_color_shader = std::unique_ptr<shader>(
            shader_factory::create_from_file("assets/shaders/flat_color.glsl"));

        shader_registry::register_("flat_color", &*_flat_color_shader).panic_on_error();
    }
}
