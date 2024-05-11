#pragma once
#include "atom/engine/ecs.h"
#include "drawers/property_drawer.h"

namespace atom::editor
{
    class transform_component_drawer: public property_drawer
    {
    public:
        transform_component_drawer() {}

    public:
        virtual auto draw() -> void override
        {
            ImGui::Text("transform component");
        }

        virtual auto get_heading() -> string_view override
        {
            return "transform component";
        }

        auto set_component(engine::transform_component* transform) -> void
        {
            _transform = transform;
        }

    private:
        engine::transform_component* _transform;
    };
}
