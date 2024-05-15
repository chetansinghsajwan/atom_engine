module;
#include "imgui.h"
#include "imgui_internal.h"

export module atom.engine:gui;

export namespace atom::engine
{
    using ::ImGuiContext;
    using ::ImGuiIO;
    using ::ImGuiStyle;
    using ::ImGuiStyleVar;
    using ::ImGuiTreeNodeFlags;
    using ::ImGuiDockNodeFlags;
    using ::ImGuiWindowFlags;
    using ::ImGuiID;
    using ::ImGuiViewport;
    using ::ImVec2;
    using ::ImVec4;

    using ::GImGui;
}

export namespace atom::engine::ImGui
{
    using namespace ::ImGui;

    using ::ImGui::Begin;
    using ::ImGui::BeginPopup;
    using ::ImGui::GetID;
    using ::ImGui::DockSpace;
    using ::ImGui::BeginMenu;
    using ::ImGui::BeginMenuBar;
    using ::ImGui::EndMenu;
    using ::ImGui::EndMenuBar;
    using ::ImGui::GetContentRegionAvail;
    using ::ImGui::IsWindowFocused;
    using ::ImGui::Image;
    using ::ImGui::BeginPopupContextItem;
    using ::ImGui::BeginPopupContextWindow;
    using ::ImGui::Button;
    using ::ImGui::CalcItemWidth;
    using ::ImGui::CloseCurrentPopup;
    using ::ImGui::Columns;
    using ::ImGui::DragFloat;
    using ::ImGui::End;
    using ::ImGui::EndPopup;
    using ::ImGui::GetIO;
    using ::ImGui::GetStyle;
    using ::ImGui::GetWindowWidth;
    using ::ImGui::InputText;
    using ::ImGui::IsItemClicked;
    using ::ImGui::IsMouseDown;
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
    using ::ImGui::Text;
    using ::ImGui::TreeNodeEx;
    using ::ImGui::TreePop;
    using ::ImGui::GetMainViewport;
    using ::ImGui::SetNextWindowPos;
    using ::ImGui::SetNextWindowSize;
    using ::ImGui::SetNextWindowViewport;
}
