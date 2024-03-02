#include "atom/engine/layers/layer.h"
#include "atom/engine/window/window_events.h"

#include "GLFW/glfw3.h"
#include "backends/imgui_impl_opengl3.h"

namespace atom::engine
{
    class imgui_layer: public layer
    {
    public:
        imgui_layer()
            : layer("imgui_layer")
            , _time(0)
        {}

    public:
        virtual auto on_attach() -> void override final
        {
            ImGui::CreateContext();
            ImGui::StyleColorsDark();

            ImGuiIO& io = ImGui::GetIO();
            io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
            io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

            // todo: user atom.engine key codes.
            io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
            io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
            io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
            io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
            io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
            io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
            io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
            io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
            io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
            io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
            io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
            io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
            io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
            io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
            io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
            io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
            io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
            io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
            io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
            io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
            io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

            ImGui_ImplOpenGL3_Init("#version 410");
        }

        virtual auto on_update() -> void override final
        {
            ImGuiIO& io = ImGui::GetIO();
            window_coords window_size = application::get()->get_window()->get_size();
            io.DisplaySize =
                ImVec2(window_size.x.to_unwrapped<float>(), window_size.y.to_unwrapped<float>());

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

        virtual auto on_deattach() -> void override final {}

        virtual auto on_window_event(window_event& event) -> void override final {}

    private:
        double _time;
    };
}
