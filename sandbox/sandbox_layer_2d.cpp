import atom.core;
import atom.logging;

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
    {
        _setup_logging();
    }

    sandbox_layer_2d::~sandbox_layer_2d()
    {
        delete _rpg_texture;
        delete _stairs_sprite;
        delete _barrel_sprite;
        delete _logger;
    }

    auto sandbox_layer_2d::on_attach() -> void
    {
        _logger->log_info("sandbox_layer_2d attached.");

        _setup_window();
        _setup_keyboard();
        _setup_mouse();

        _camera_controller.set_window(_window);
        _camera_controller.set_keyboard(_keyboard);
        _camera_controller.set_mouse(_mouse);

        _rpg_texture = texture2d::create(
            "/home/chetan/projects/atom.engine/sandbox/assets/textures/rpg-pack.png");

        _stairs_sprite = sprite::make_from_coords(_rpg_texture, vec2(7, 6), vec2(128, 128));
        _barrel_sprite = sprite::make_from_coords(_rpg_texture, vec2(8, 2), vec2(128, 128));
        _tree_sprite =
            sprite::make_from_coords(_rpg_texture, vec2(2, 1), vec2(128, 128), vec2(1, 2));
    }

    auto sandbox_layer_2d::on_update(time_step delta_time) -> void
    {
        _camera_controller.on_update(delta_time);

        renderer_2d::reset_stats();

        render_command::set_clear_color({ 0.1f, 0.1f, 0.1f, 1 });
        render_command::clear_color();

        renderer_2d::begin_scene(_camera_controller.get_camera());

        renderer_2d::draw_sprite(vec3(), vec2(1, 1), 0, _stairs_sprite);
        renderer_2d::draw_sprite(vec3(1, 0, 0), vec2(1, 1), 0, _barrel_sprite);
        renderer_2d::draw_sprite(vec3(-1, 0, 0), vec2(1, 2), 0, _tree_sprite);

        renderer_2d::end_scene();
    }

    auto sandbox_layer_2d::on_imgui_render() -> void
    {
        ImGui::Begin("settings");

        renderer_2d::statistics stats = renderer_2d::get_stats();
        ImGui::Text("-- Renderer2D Stats -----------------------------------");
        ImGui::Text("Draw Calls: %d", stats.draw_calls);
        ImGui::Text("Quads: %d", stats.quad_count);
        ImGui::Text("Vertices: %d", stats.get_total_vertex_count());
        ImGui::Text("Indices: %d", stats.get_total_index_count());

        u32 renderer_id = _rpg_texture->get_renderer_id();
        ImGui::Image(reinterpret_cast<void*>(renderer_id), ImVec2(1280, 720));

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
