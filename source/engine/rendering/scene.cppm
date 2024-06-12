export module atom.engine:rendering.scene;

import atom.core;
import entt;
import :box2d;
import :ecs;
import :time;
import :math;
import :rendering.renderer_2d;

namespace atom::engine
{
    export class scene
    {
    public:
        scene(entity_manager* manager)
            : _entity_manager{ manager }
        {}

        ~scene() {}

    public:
        auto on_start() -> void {}

        auto on_update(time_step time) -> void {}

        auto on_stop() -> void {}

        auto get_entity_manager() const -> entity_manager*
        {
            return _entity_manager;
        }

    private:
        entity_manager* _entity_manager;
        u32 _viewport_width;
        u32 _viewport_height;
    };
}
