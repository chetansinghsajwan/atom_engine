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
        , _quad_color(.2f, .3f, .8f, 1)
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

    auto sandbox_layer_2d::on_update(time_stemp delta_time) -> void
    {
        _camera_controller.on_update(delta_time);

        renderer_2d::reset_stats();

        render_command::set_clear_color({ 0.1f, 0.1f, 0.1f, 1 });
        render_command::clear_color();

        renderer_2d::begin_scene(_camera_controller.get_camera());

        renderer_2d::draw_sprite(renderer_2d::sprite_draw_data{
            .sprite = _stairs_sprite,
            .position = vec3(),
            .size = vec2(1, 1),
            .rotation = 0,
        });

        renderer_2d::draw_sprite(renderer_2d::sprite_draw_data{
            .sprite = _barrel_sprite,
            .position = vec3(1, 0, 0),
            .size = vec2(1, 1),
            .rotation = 0,
        });

        renderer_2d::draw_sprite(renderer_2d::sprite_draw_data{
            .sprite = _tree_sprite,
            .position = vec3(-1, 0, 0),
            .size = vec2(1, 2),
            .rotation = 0,
        });

        renderer_2d::end_scene();
    }

    auto sandbox_layer_2d::on_imgui_render() -> void
    {
        static bool enable_docking = true;
        if (enable_docking)
        {
            static bool is_dockspace_open = true;
            static bool opt_fullscreen_persistant = true;
            bool opt_fullscreen = opt_fullscreen_persistant;
            static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

            // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
            // because it would be confusing to have two docking targets within each others.
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
            if (opt_fullscreen)
            {
                ImGuiViewport* viewport = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(viewport->Pos);
                ImGui::SetNextWindowSize(viewport->Size);
                ImGui::SetNextWindowViewport(viewport->ID);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
                window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse
                                | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
                window_flags |=
                    ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
            }

            // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
            if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
                window_flags |= ImGuiWindowFlags_NoBackground;

            // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
            // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
            // all active windows docked into it will lose their parent and become undocked.
            // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
            // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            ImGui::Begin("DockSpace Demo", &is_dockspace_open, window_flags);
            ImGui::PopStyleVar();

            if (opt_fullscreen)
                ImGui::PopStyleVar(2);

            // DockSpace
            ImGuiIO& io = ImGui::GetIO();
            if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
            {
                ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
                ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
            }

            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    // Disabling fullscreen would allow the window to be moved to the front of other windows,
                    // which we can't undo at the moment without finer window depth/z control.
                    //ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

                    if (ImGui::MenuItem("Exit"))
                        application::get()->stop();

                    ImGui::EndMenu();
                }

                ImGui::EndMenuBar();
            }

            {
                ImGui::Begin("settings");

                renderer_2d::statistics stats = renderer_2d::get_stats();
                ImGui::Text("-- Renderer2D Stats -----------------------------------");
                ImGui::Text("Draw Calls: %d", stats.draw_calls);
                ImGui::Text("Quads: %d", stats.quad_count);
                ImGui::Text("Vertices: %d", stats.get_total_vertex_count());
                ImGui::Text("Indices: %d", stats.get_total_index_count());

                ImGui::ColorEdit4("quad color", glm::value_ptr(_quad_color));

                ImGui::End();
            }

            ImGui::End();
        }
        else
        {
            ImGui::Begin("settings");

            renderer_2d::statistics stats = renderer_2d::get_stats();
            ImGui::Text("-- Renderer2D Stats -----------------------------------");
            ImGui::Text("Draw Calls: %d", stats.draw_calls);
            ImGui::Text("Quads: %d", stats.quad_count);
            ImGui::Text("Vertices: %d", stats.get_total_vertex_count());
            ImGui::Text("Indices: %d", stats.get_total_index_count());

            ImGui::ColorEdit4("quad color", glm::value_ptr(_quad_color));

            ImGui::End();
        }
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
