#include "panels/entity_explorer_panel.h"
#include "imgui.h"

namespace atom::editor
{
    auto entity_explorer_panel::on_imgui_render() -> void
    {
        ImGui::Begin("entity heirarchy");

        for (auto entry : _manager->view_all())
        {
            engine::entity* entity = &std::get<1>(entry);

            ImGuiStyle& style = ImGui::GetStyle();
            style.WindowMinSize.x = 370;

            ImGuiTreeNodeFlags flags =
                ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
            if (_selected_entity == entity)
            {
                flags |= ImGuiTreeNodeFlags_Selected;
            }

            bool opened = ImGui::TreeNodeEx(
                (void*)entity->get_id(), flags, "%s", entity->get_name().get_data());
            if (ImGui::IsItemClicked())
            {
                _selected_entity = entity;
            }

            bool delete_entity = false;
            if (ImGui::BeginPopupContextItem())
            {
                if (ImGui::MenuItem("delete entity"))
                {
                    delete_entity = true;
                }

                ImGui::EndPopup();
            }

            if (opened)
            {
                ImGui::TreePop();
            }

            if (delete_entity)
            {
                _manager->destroy_entity(entity);
                if (entity == _selected_entity)
                {
                    _selected_entity = nullptr;
                }
            }
        }

        if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
        {
            _selected_entity = nullptr;
        }

        if (ImGui::BeginPopupContextWindow(
                0, ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems))
        {
            if (ImGui::MenuItem("create entity"))
            {
                _manager->create_entity("new entity");
            }

            ImGui::EndPopup();
        }

        ImGui::End();
    }
}
