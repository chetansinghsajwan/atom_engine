#include "imgui_layer.h"
#include "atom/engine/application.h"
#include "engine/imgui/imgui_keyboard_key_conversions.h"

#include "GLFW/glfw3.h"
#include "backends/imgui_impl_opengl3.h"
#include "glad/glad.h"
#include "imgui.h"

namespace atom::engine
{
    static auto handle_window_focus_event(window_focus_event& event) -> void
    {
        ImGuiIO& io = ImGui::GetIO();
        io.AddFocusEvent(event.is_focused);
    }

    static auto handle_window_resize_event(window_resize_event& event) -> void
    {
        ImGuiIO& io = ImGui::GetIO();

        float x = event.size.x.to_unwrapped<float>();
        float y = event.size.y.to_unwrapped<float>();

        io.DisplaySize = ImVec2(x, y);
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        glViewport(0, 0, x, y);
    }

    static auto handle_keyboard_key_event(keyboard_key_event& event) -> void
    {
        ImGuiIO& io = ImGui::GetIO();

        ImGuiKey imgui_key = imgui_atom_key_to_imgui_key(event.key);
        bool imgui_down = imgui_is_atom_keyboard_key_state_down(event.state);
        io.AddKeyEvent(imgui_key, imgui_down);
    }

    static auto handle_keyboard_char_event(keyboard_char_event& event) -> void
    {
        ImGuiIO& io = ImGui::GetIO();
        io.AddInputCharacter((unsigned int)event.ch.to_unwrapped());
    }

    static auto handle_mouse_button_event(mouse_button_event& event) -> void
    {
        ImGuiIO& io = ImGui::GetIO();

        ImGuiMouseButton_ imgui_button = imgui_atom_button_to_imgui_button(event.button);
        bool imgui_down = imgui_is_atom_mouse_button_state_down(event.state);
        if (imgui_button != ImGuiMouseButton_COUNT)
            io.AddMouseButtonEvent(imgui_button, imgui_down);
    }

    static auto handle_mouse_move_event(mouse_move_event& event) -> void
    {
        ImGuiIO& io = ImGui::GetIO();
        io.AddMousePosEvent(event.xpos.to_unwrapped<float>(), event.ypos.to_unwrapped<float>());
    }

    static auto handle_mouse_scroll_event(mouse_scroll_event& event) -> void
    {
        ImGuiIO& io = ImGui::GetIO();
        io.AddMouseWheelEvent(
            event.xoffset.to_unwrapped<float>(), event.yoffset.to_unwrapped<float>());
    }

    auto imgui_layer::on_attach() -> void
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        ImGui_ImplOpenGL3_Init("#version 410");

        window_coords window_size = application::get()->get_window()->get_size();
        io.DisplaySize =
            ImVec2(window_size.x.to_unwrapped<float>(), window_size.y.to_unwrapped<float>());
    }

    auto imgui_layer::on_update() -> void
    {
        ImGuiIO& io = ImGui::GetIO();

        double time = glfwGetTime();
        io.DeltaTime = _time > 0.0 ? (time - _time) : (1.0 / 60.0);
        _time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    auto imgui_layer::on_deattach() -> void
    {
        ImGui_ImplOpenGL3_Shutdown();
    }

    auto imgui_layer::handle(window_event& event) -> void
    {
        switch (event.event_type)
        {
            case window_event_type::focus:
            {
                window_focus_event& focus_event = reinterpret_cast<window_focus_event&>(event);
                handle_window_focus_event(focus_event);
                break;
            }

            case window_event_type::resize:
            {
                window_resize_event& resize_event = reinterpret_cast<window_resize_event&>(event);
                handle_window_resize_event(resize_event);
                break;
            }

            default: break;
        }
    }

    auto imgui_layer::handle(keyboard_event& event) -> void
    {
        switch (event.event_type)
        {
            case keyboard_event_type::key_event:
            {
                keyboard_key_event& key_event = reinterpret_cast<keyboard_key_event&>(event);
                handle_keyboard_key_event(key_event);
                break;
            }

            case keyboard_event_type::char_event:
            {
                keyboard_char_event& char_event = reinterpret_cast<keyboard_char_event&>(event);
                handle_keyboard_char_event(char_event);
                break;
            }

            default: break;
        }
    }

    auto imgui_layer::handle(mouse_event& event) -> void
    {
        switch (event.event_type)
        {
            case mouse_event_type::button_event:
            {
                mouse_button_event& button_event = reinterpret_cast<mouse_button_event&>(event);
                handle_mouse_button_event(button_event);
                break;
            }

            case mouse_event_type::move_event:
            {
                mouse_move_event& move_event = reinterpret_cast<mouse_move_event&>(event);
                handle_mouse_move_event(move_event);
                break;
            }

            case mouse_event_type::scroll_event:
            {
                mouse_scroll_event& scroll_event = reinterpret_cast<mouse_scroll_event&>(event);
                handle_mouse_scroll_event(scroll_event);
                break;
            }

            default: break;
        }
    }
}
