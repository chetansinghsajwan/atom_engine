export module atom_engine:world;

import :ecs;
import :time;

namespace atom::engine
{
    export class world
    {
    public:
        world();
        ~world();

    public:
        auto get_system_manager() -> system_manager*;
        auto get_entity_manager() -> entity_manager*;

        auto on_update(time_step time) -> void;

    private:
        system_manager* _system_manager;
        entity_manager* _entity_manager;
    };
}
