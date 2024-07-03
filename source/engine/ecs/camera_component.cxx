module atom_engine:ecs.camera_component.impl;

import :ecs.camera_component;
import :ecs.entity_component;
import :rendering.scene_camera;

namespace atom::engine
{
    camera_component::camera_component()
        : _camera{}
    {}

    camera_component::~camera_component() {}

    auto camera_component::get_camera() -> scene_camera&
    {
        return _camera;
    }
}
