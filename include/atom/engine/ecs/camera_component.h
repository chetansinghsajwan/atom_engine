#pragma once
#include "atom/engine/ecs/entity_component.h"
#include "engine/rendering/scene_camera.h"

namespace atom::engine
{
    class camera_component: public entity_component
    {
    public:
        camera_component()
            : _camera{}
        {}

        ~camera_component() {}

    public:
        auto get_camera() -> scene_camera&
        {
            return _camera;
        }

    private:
        scene_camera _camera;
    };
}
