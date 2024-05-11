#pragma once
#include "atom/engine/ecs.h"
#include "drawers/property_drawer.h"

namespace atom::editor
{
    class sprite_component_drawer: public property_drawer
    {
    public:
        sprite_component_drawer() {}

    public:
        virtual auto draw() -> void override
        {
            ImGui::Text("sprite component");
        }

        virtual auto get_heading() -> string_view override
        {
            return "sprite component";
        }

        auto set_component(engine::sprite_component* sprite) -> void
        {
            _transform = sprite;
        }

    private:
        engine::sprite_component* _transform;
    };
}
