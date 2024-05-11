#pragma once
#include "atom/engine/ecs.h"
#include "drawers/property_drawer.h"

namespace atom::editor
{
    class camera_component_drawer: public property_drawer
    {
    public:
        camera_component_drawer() {}

    public:
        virtual auto draw() -> void override
        {
            ImGui::Text("camera component");
        }

        virtual auto set_property(void* property) -> void override
        {
            _camera_component = reinterpret_cast<engine::camera_component*>(property);
        }

    private:
        engine::camera_component* _camera_component;
    };
}
