import atom.core;
import atom.logging;

#include "panels/inspector_panel.h"
#include "atom/engine/ecs/camera_component.h"
#include "atom/engine/ecs/sprite_component.h"
#include "drawers/property_drawer_provider.h"
#include "imgui.h"

namespace atom::editor
{
    auto inspector_panel::on_imgui_render() -> void
    {
        ImGui::Begin("inspector");

        if (_entity != nullptr)
        {
            string_view entity_name = _entity->get_name();

            // todo: replace this with a atom.core.buffer helper class.
            char buffer[100];
            std::copy(
                entity_name.get_data(), entity_name.get_data() + entity_name.get_count(), buffer);

            if (ImGui::InputText("name", buffer, sizeof(buffer)))
            {
                _entity->set_name(string_view::from_cstr(buffer, sizeof(buffer)));
            }

            for (engine::entity_component* component : _entity->get_all_components())
            {
                property_drawer* drawer = property_drawer_provider::get(component);
                if (drawer == nullptr)
                    continue;

                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
                bool opened = ImGui::TreeNodeEx(drawer->get_id(),
                    ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap,
                    "%s", drawer->get_property_name().get_data());

                ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
                if (ImGui::Button("+", ImVec2{ 20, 20 }))
                {
                    ImGui::OpenPopup("component options");
                }
                ImGui::PopStyleVar();

                bool remove_component = false;
                if (ImGui::BeginPopup("component options"))
                {
                    if (ImGui::MenuItem("remove component"))
                        remove_component = true;

                    ImGui::EndPopup();
                }

                if (opened)
                {
                    drawer->set_property(component);
                    drawer->draw();

                    ImGui::TreePop();
                }

                if (remove_component)
                {
                    _entity->remove_component(component);
                }
            }

            if (ImGui::Button("add component"))
            {
                ImGui::OpenPopup("add component");
            }

            if (ImGui::BeginPopup("add component"))
            {
                if (ImGui::MenuItem("camera component"))
                {
                    _entity->emplace_component<engine::camera_component>();
                    ImGui::CloseCurrentPopup();
                }

                if (ImGui::MenuItem("sprite component"))
                {
                    _entity->emplace_component<engine::sprite_component>();
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }
        }

        ImGui::End();
    }
}
