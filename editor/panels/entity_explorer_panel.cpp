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

            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
            if (_selected_entity == entity)
            {
                flags |= ImGuiTreeNodeFlags_Selected;
            }

            bool opened = ImGui::TreeNodeEx(
                (void*)(uint64_t)(uint32_t)entity->get_id(), flags, "%s", entity->get_name().get_data());
            if (ImGui::IsItemClicked())
            {
                _selected_entity = entity;
            }

            if (opened)
            {
                ImGui::TreePop();
            }
        }

        ImGui::End();
    }
}
