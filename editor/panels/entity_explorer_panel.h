#pragma once
#include "atom/engine/ecs.h"

namespace atom::editor
{
    class entity_explorer_panel
    {
    public:
        entity_explorer_panel(engine::entity_manager* manager)
            : _manager{ manager }
        {}

        ~entity_explorer_panel() {}

    public:
        auto on_imgui_render() -> void;

    private:
        engine::entity_manager* _manager;
        engine::entity* _selected_entity;
    };
}
