module atom.engine:world.impl;

import :ecs;
import :world;
import :time;

namespace atom::engine
{
    world::world()
    {
        _system_manager = new system_manager{};
        _entity_manager = new entity_manager{};
    }

    world::~world()
    {
        delete _system_manager;
        delete _entity_manager;
    }

    auto world::on_update(time_step time) -> void
    {
        _system_manager->update_systems(time);
    }

    auto world::get_system_manager() -> system_manager*
    {
        return _system_manager;
    }

    auto world::get_entity_manager() -> entity_manager*
    {
        return _entity_manager;
    }
}
