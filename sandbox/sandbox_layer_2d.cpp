#include "sandbox_layer_2d.h"
#include "atom/engine/rendering/shader_factory.h"
#include "atom/engine/rendering/shader_registry.h"
#include "atom/engine/window/window_manager.h"
#include "engine/rendering/renderer.h"
#include "engine/rendering/renderer_2d.h"
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

    sandbox_layer_2d::~sandbox_layer_2d() {}

    auto sandbox_layer_2d::on_attach() -> void
    {
        _logger->log_info("sandbox_layer_2d attached.");

        _setup_window();
        _setup_keyboard();
        _setup_mouse();

        _camera_controller.set_window(_window);
        _camera_controller.set_keyboard(_keyboard);
        _camera_controller.set_mouse(_mouse);

        _checkerboard_texture = texture2d::create(
            "/home/chetan/projects/atom.engine/sandbox/assets/textures/checkerboard.png");
    }

    auto sandbox_layer_2d::on_update(time_stemp delta_time) -> void
    {
        _camera_controller.on_update(delta_time);

        render_command::set_clear_color({ 0.1f, 0.1f, 0.1f, 1 });
        render_command::clear_color();

        renderer_2d::begin_scene(_camera_controller.get_camera());
        // renderer_2d::draw_quad({ -1.0f, 0.0f, 0 }, { 0.8f, 0.8f }, 0, { 0.8f, 0.2f, 0.3f, 1.0f });
        // renderer_2d::draw_quad({ 0.5f, -0.5f, 0 }, { 0.5f, 0.75f }, 0, { 0.2f, 0.3f, 0.8f, 1.0f });
        // renderer_2d::draw_quad(vec3(.5, -.5, 0), vec2(.5, .75), glm::radians(.0), vec4(.8, .2, .3, 1));
        // renderer_2d::draw_texture(vec3(0, 0, -.1), vec2(10, 10), glm::radians(45.), _checkerboard_texture, 10, vec4(1, .9, .9, 1));
        renderer_2d::draw_quad(vec3(0, 0, 0), vec2(1, 1), 0, _square_color);
        renderer_2d::draw_quad(vec3(1.1f, 1.1f, 0), vec2(1, 1), 0, _square_color);
        renderer_2d::end_scene();
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
}
