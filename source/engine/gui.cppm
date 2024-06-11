module;
#include "imgui.h"
#include "imgui_internal.h"

export module atom.engine:gui;

import atom.core;
import :math;

export namespace atom::engine
{
    using ::ImGuiContext;
    using ::ImGuiDockNodeFlags;
    using ::ImGuiID;
    using ::ImGuiIO;
    using ::ImGuiStyle;
    using ::ImGuiStyleVar;
    using ::ImGuiStyleVar_;
    using ::ImGuiTreeNodeFlags;
    using ::ImGuiViewport;
    using ::ImGuiWindowFlags;
    using ::ImVec2;
    using ::ImVec4;

    using ::GImGui;
}

export namespace atom::engine::ImGui
{
    using namespace ::ImGui;

    using ::ImGui::Begin;
    using ::ImGui::BeginMenu;
    using ::ImGui::BeginMenuBar;
    using ::ImGui::BeginPopup;
    using ::ImGui::BeginPopupContextItem;
    using ::ImGui::BeginPopupContextWindow;
    using ::ImGui::Button;
    using ::ImGui::CalcItemWidth;
    using ::ImGui::CloseCurrentPopup;
    using ::ImGui::Columns;
    using ::ImGui::DockSpace;
    using ::ImGui::DragFloat;
    using ::ImGui::End;
    using ::ImGui::EndMenu;
    using ::ImGui::EndMenuBar;
    using ::ImGui::EndPopup;
    using ::ImGui::GetContentRegionAvail;
    using ::ImGui::GetID;
    using ::ImGui::GetIO;
    using ::ImGui::GetMainViewport;
    using ::ImGui::GetStyle;
    using ::ImGui::GetWindowWidth;
    using ::ImGui::Image;
    using ::ImGui::InputText;
    using ::ImGui::IsItemClicked;
    using ::ImGui::IsMouseDown;
    using ::ImGui::IsWindowFocused;
    using ::ImGui::IsWindowHovered;
    using ::ImGui::MenuItem;
    using ::ImGui::NextColumn;
    using ::ImGui::OpenPopup;
    using ::ImGui::PopID;
    using ::ImGui::PopItemWidth;
    using ::ImGui::PopStyleColor;
    using ::ImGui::PopStyleVar;
    using ::ImGui::PushID;
    using ::ImGui::PushMultiItemsWidths;
    using ::ImGui::PushStyleColor;
    using ::ImGui::PushStyleVar;
    using ::ImGui::SameLine;
    using ::ImGui::SetColumnWidth;
    using ::ImGui::SetNextWindowPos;
    using ::ImGui::SetNextWindowSize;
    using ::ImGui::SetNextWindowViewport;
    using ::ImGui::Text;
    using ::ImGui::TreeNodeEx;
    using ::ImGui::TreePop;
}

export namespace atom::engine::gui
{
    auto draw_image(u32 user_texture_id, const vec2& image_size, const vec2& uv0 = { 0, 0 },
        const vec2& uv1 = { 1, 1 }, const vec4& tint_col = { 1, 1, 1, 1 },
        const vec4& border_col = { 0, 0, 0, 0 }) -> void
    {
        void* imgui_user_texture_id = reinterpret_cast<void*>(user_texture_id);
        ImVec2 imgui_image = { image_size.x, image_size.y };
        ImVec2 imgui_uv0 = { uv0.x, uv0.y };
        ImVec2 imgui_uv1 = { uv1.x, uv1.y };
        ImVec4 imgui_tint_col = { tint_col.x, tint_col.y, tint_col.z, tint_col.w };
        ImVec4 imgui_border_col = { border_col.x, border_col.y, border_col.z, border_col.w };

        ImGui::Image(imgui_user_texture_id, imgui_image, imgui_uv0, imgui_uv1, imgui_tint_col,
            imgui_border_col);
    }

    auto get_content_region_available() -> f32vec2
    {
        ImVec2 imgui_vec = ImGui::GetContentRegionAvail();
        return { imgui_vec.x, imgui_vec.y };
    }

    auto begin(string_view str) -> void
    {
        ImGui::Begin(str.get_data());
    }

    auto end() -> void
    {
        ImGui::End();
    }
}
