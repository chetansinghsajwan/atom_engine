export module atom.engine:ecs.camera_component;

import :ecs.entity_component;
import :rendering.scene_camera;

namespace atom::engine
{
    export class camera_component: public entity_component
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
