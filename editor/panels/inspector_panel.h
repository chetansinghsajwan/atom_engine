#pragma once
#include "panels/panel.h"
#include "atom/engine/ecs.h"

namespace atom::editor
{
    class inspector_panel: public panel
    {
    public:
        virtual auto on_imgui_render() -> void override;

        auto set_entity(engine::entity* entity) -> void
        {
            _entity = entity;
        }

    private:
        auto _draw_component(engine::entity_component* component) -> void;

    private:
        engine::entity* _entity;
    };
}
