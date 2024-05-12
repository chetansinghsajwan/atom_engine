#pragma once
#include "atom/core/string/string_view.h"
#include "atom/engine/ecs.h"
#include "drawers/property_drawer.h"
#include "imgui_internal.h"

namespace atom::editor
{
    class transform_component_drawer: public property_drawer
    {
    public:
        transform_component_drawer() {}

    public:
        virtual auto draw() -> void override
        {
            if (_transform == nullptr)
                return;

            engine::vec3 position = _transform->get_position();
            _draw_vec3("position", &position);
            _transform->set_position(position);

            engine::vec3 rotation = engine::math::degrees(_transform->get_rotation());
            _draw_vec3("rotation", &rotation);
            _transform->set_rotation(engine::math::radians(rotation));

            engine::vec3 scale = _transform->get_scale();
            _draw_vec3("scale", &scale);
            _transform->set_scale(scale);
        }

        virtual auto set_property(void* property) -> void override
        {
            _transform = reinterpret_cast<engine::transform_component*>(property);
        }

        virtual auto get_property_name() -> string_view override
        {
            return "transform component";
        }

        virtual auto get_id() -> void* override
        {
            return (void*)typeid(engine::transform_component).hash_code();
        }

    private:
        auto _draw_vec3(string_view label, engine::vec3* values,
            engine::vec3 reset_values = { 0, 0, 0 }, float column_width = 100) -> void
        {
            ImGui::PushID(label.get_data());

            ImGui::Columns(2);
            ImGui::SetColumnWidth(0, column_width);
            ImGui::Text("%s", label.get_data());
            ImGui::NextColumn();

            ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

            float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
            ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
            if (ImGui::Button("X", buttonSize))
            {
                values->x = reset_values.x;
            }
            ImGui::PopStyleColor(3);

            ImGui::SameLine();
            ImGui::DragFloat("##X", &values->x, 0.1f, 0.0f, 0.0f, "%.2f");
            ImGui::PopItemWidth();
            ImGui::SameLine();

            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
            if (ImGui::Button("Y", buttonSize))
            {
                values->y = reset_values.y;
            }
            ImGui::PopStyleColor(3);

            ImGui::SameLine();
            ImGui::DragFloat("##Y", &values->y, 0.1f, 0.0f, 0.0f, "%.2f");
            ImGui::PopItemWidth();
            ImGui::SameLine();

            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
            if (ImGui::Button("Z", buttonSize))
            {
                values->z = reset_values.z;
            }
            ImGui::PopStyleColor(3);

            ImGui::SameLine();
            ImGui::DragFloat("##Z", &values->z, 0.1f, 0.0f, 0.0f, "%.2f");
            ImGui::PopItemWidth();

            ImGui::PopStyleVar();

            ImGui::Columns(1);

            ImGui::PopID();
        }

    private:
        engine::transform_component* _transform;
    };
}
