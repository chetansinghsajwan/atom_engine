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

        virtual auto get_heading() -> string_view override
        {
            return "camera component";
        }

        auto set_component(engine::camera_component* camera) -> void
        {
            _transform = camera;
        }

    private:
        engine::camera_component* _transform;
    };
}
