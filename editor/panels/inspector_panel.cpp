#include "panels/inspector_panel.h"
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

                drawer->set_property(component);
                drawer->draw();
            }
        }

        ImGui::End();
    }
}
