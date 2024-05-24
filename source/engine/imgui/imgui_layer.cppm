module;

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

export module atom.engine:imgui.layer;

import atom.core;
import :glfw;
import :application;

namespace atom::engine
{
    class imgui_layer: public layer
    {
    public:
        imgui_layer()
            : layer{ "imgui_layer" }
            , _time{ 0 }
        {}

    public:
        virtual auto on_attach() -> void override
        {
            glfw_window* window = (glfw_window*)application::get()->get_window();

            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGui::StyleColorsDark();
            ImGuiIO& io = ImGui::GetIO();

            io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
            io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

            ImGui_ImplGlfw_InitForOpenGL(window->get_native_glfw(), true);
            ImGui_ImplOpenGL3_Init("#version 410");

            setup_imgui_theme();
        }

        virtual auto on_deattach() -> void override
        {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }

        auto begin_render() -> void
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }

        virtual auto on_imgui_render() -> void override {}

        auto end_render() -> void
        {
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            ImGuiIO& io = ImGui::GetIO();

            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                GLFWwindow* backup_current_context = glfwGetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_current_context);
            }
        }

        auto setup_imgui_theme() -> void
        {
            // theme name: embrace the darkness

            ImVec4* colors = ImGui::GetStyle().Colors;
            colors[ImGuiCol_Text] = ImVec4{ 1, 1, 1, 1 };
            colors[ImGuiCol_TextDisabled] = ImVec4{ .50, .50, .50, 1 };
            colors[ImGuiCol_WindowBg] = ImVec4{ .10, .10, .10, 1 };
            colors[ImGuiCol_ChildBg] = ImVec4{ 0, 0, 0, 0 };
            colors[ImGuiCol_PopupBg] = ImVec4{ .19, .19, .19, .92 };
            colors[ImGuiCol_Border] = ImVec4{ .19, .19, .19, .29 };
            colors[ImGuiCol_BorderShadow] = ImVec4{ 0, 0, 0, .24 };
            colors[ImGuiCol_FrameBg] = ImVec4{ .05, .05, .05, .54 };
            colors[ImGuiCol_FrameBgHovered] = ImVec4{ .19, .19, .19, .54 };
            colors[ImGuiCol_FrameBgActive] = ImVec4{ .20, .22, .23, 1 };
            colors[ImGuiCol_TitleBg] = ImVec4{ 0, 0, 0, 1 };
            colors[ImGuiCol_TitleBgActive] = ImVec4{ .06, .06, .06, 1 };
            colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0, 0, 0, 1 };
            colors[ImGuiCol_MenuBarBg] = ImVec4{ .14, .14, .14, 1 };
            colors[ImGuiCol_ScrollbarBg] = ImVec4{ .05, .05, .05, .54 };
            colors[ImGuiCol_ScrollbarGrab] = ImVec4{ .34, .34, .34, .54 };
            colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4{ .40, .40, .40, .54 };
            colors[ImGuiCol_ScrollbarGrabActive] = ImVec4{ .56, .56, .56, .54 };
            colors[ImGuiCol_CheckMark] = ImVec4{ .33, .67, .86, 1 };
            colors[ImGuiCol_SliderGrab] = ImVec4{ .34, .34, .34, .54 };
            colors[ImGuiCol_SliderGrabActive] = ImVec4{ .56, .56, .56, .54 };
            colors[ImGuiCol_Button] = ImVec4{ .05, .05, .05, .54 };
            colors[ImGuiCol_ButtonHovered] = ImVec4{ .19, .19, .19, .54 };
            colors[ImGuiCol_ButtonActive] = ImVec4{ .20, .22, .23, 1 };
            colors[ImGuiCol_Header] = ImVec4{ 0, 0, 0, .52 };
            colors[ImGuiCol_HeaderHovered] = ImVec4{ 0, 0, 0, .36 };
            colors[ImGuiCol_HeaderActive] = ImVec4{ .20, .22, .23, .33 };
            colors[ImGuiCol_Separator] = ImVec4{ .28, .28, .28, .29 };
            colors[ImGuiCol_SeparatorHovered] = ImVec4{ .44, .44, .44, .29 };
            colors[ImGuiCol_SeparatorActive] = ImVec4{ .40, .44, .47, 1 };
            colors[ImGuiCol_ResizeGrip] = ImVec4{ .28, .28, .28, .29 };
            colors[ImGuiCol_ResizeGripHovered] = ImVec4{ .44, .44, .44, .29 };
            colors[ImGuiCol_ResizeGripActive] = ImVec4{ .40, .44, .47, 1 };
            colors[ImGuiCol_Tab] = ImVec4{ 0, 0, 0, .52 };
            colors[ImGuiCol_TabHovered] = ImVec4{ .14, .14, .14, 1 };
            colors[ImGuiCol_TabActive] = ImVec4{ .20, .20, .20, .36 };
            colors[ImGuiCol_TabUnfocused] = ImVec4{ 0, 0, 0, .52 };
            colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ .14, .14, .14, 1 };
            colors[ImGuiCol_DockingPreview] = ImVec4{ .33, .67, .86, 1 };
            colors[ImGuiCol_DockingEmptyBg] = ImVec4{ 1, 0, 0, 1 };
            colors[ImGuiCol_PlotLines] = ImVec4{ 1, 0, 0, 1 };
            colors[ImGuiCol_PlotLinesHovered] = ImVec4{ 1, 0, 0, 1 };
            colors[ImGuiCol_PlotHistogram] = ImVec4{ 1, 0, 0, 1 };
            colors[ImGuiCol_PlotHistogramHovered] = ImVec4{ 1, 0, 0, 1 };
            colors[ImGuiCol_TableHeaderBg] = ImVec4{ 0, 0, 0, .52 };
            colors[ImGuiCol_TableBorderStrong] = ImVec4{ 0, 0, 0, .52 };
            colors[ImGuiCol_TableBorderLight] = ImVec4{ .28, .28, .28, .29 };
            colors[ImGuiCol_TableRowBg] = ImVec4{ 0, 0, 0, 0 };
            colors[ImGuiCol_TableRowBgAlt] = ImVec4{ 1, 1, 1, .06 };
            colors[ImGuiCol_TextSelectedBg] = ImVec4{ .20, .22, .23, 1 };
            colors[ImGuiCol_DragDropTarget] = ImVec4{ .33, .67, .86, 1 };
            colors[ImGuiCol_NavHighlight] = ImVec4{ 1, 0, 0, 1 };
            colors[ImGuiCol_NavWindowingHighlight] = ImVec4{ 1, 0, 0, .70 };
            colors[ImGuiCol_NavWindowingDimBg] = ImVec4{ 1, 0, 0, .20 };
            colors[ImGuiCol_ModalWindowDimBg] = ImVec4{ 1, 0, 0, .35 };

            ImGuiStyle& style = ImGui::GetStyle();
            style.WindowPadding = ImVec2{ 8, 8 };
            style.FramePadding = ImVec2{ 5, 2 };
            style.CellPadding = ImVec2{ 6, 6 };
            style.ItemSpacing = ImVec2{ 6, 6 };
            style.ItemInnerSpacing = ImVec2{ 6, 6 };
            style.TouchExtraPadding = ImVec2{ 0, 0 };
            style.IndentSpacing = 25;
            style.ScrollbarSize = 15;
            style.GrabMinSize = 10;
            style.WindowBorderSize = 1;
            style.ChildBorderSize = 1;
            style.PopupBorderSize = 1;
            style.FrameBorderSize = 1;
            style.TabBorderSize = 1;
            style.WindowRounding = 7;
            style.ChildRounding = 4;
            style.FrameRounding = 3;
            style.PopupRounding = 4;
            style.ScrollbarRounding = 9;
            style.GrabRounding = 3;
            style.LogSliderDeadzone = 4;
            style.TabRounding = 4;
        }

    private:
        f64 _time;
    };
}
