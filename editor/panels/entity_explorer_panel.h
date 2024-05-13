#pragma once
#include "atom/engine/ecs.h"
#include "panels/panel.h"

namespace atom::editor
{
    class entity_explorer_panel: public panel
    {
    public:
        entity_explorer_panel(engine::entity_manager* manager)
            : _manager{ manager }
            , panel{}
        {}

        ~entity_explorer_panel() {}

    public:
        virtual auto on_imgui_render() -> void override;

        auto set_selected_entity(engine::entity* entity) -> void
        {
            _selected_entity = entity;
        }

        auto get_selected_entity() -> engine::entity*
        {
            return _selected_entity;
        }

    private:
        engine::entity_manager* _manager = nullptr;
        engine::entity* _selected_entity = nullptr;
    };
}
