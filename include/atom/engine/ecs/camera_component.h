#pragma once
#include "atom/engine/ecs/entity_component.h"
#include "engine/rendering/camera.h"

namespace atom::engine
{
    class camera_component: public entity_component
    {
    public:
        camera_component(const mat4& projection)
            : _camera{ projection }
        {}

        ~camera_component() {}

    public:
        auto get_camera() -> camera&
        {
            return _camera;
        }

    private:
        camera _camera;
    };
}
