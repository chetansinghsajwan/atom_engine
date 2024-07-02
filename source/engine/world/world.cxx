module atom.engine:world.impl;

import atom_core;
import :ecs;
import :world;
import :time;
import :physics;
import :rendering;

namespace atom::engine
{
    world::world()
    {
        _system_manager = new system_manager{};
        _entity_manager = new entity_manager{ this };

        _system_manager->initialize();
        _system_manager->emplace_system<physics2d_system>(this);
        _system_manager->emplace_system<render_system>(this);
    }

    world::~world()
    {
        _system_manager->finalize();

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
