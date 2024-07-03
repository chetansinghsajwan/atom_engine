module atom_engine:ecs.system.impl;

import atom_core;
import :time;
import :ecs.system;

namespace atom::engine
{
    system::system(string name, class world* world)
        : _name{ move(name) }
        , _world{ world }
    {}

    system::~system() {}

    auto system::get_name() const -> string_view
    {
        return _name;
    }

    auto system::get_world() -> world*
    {
        return _world;
    }

    auto system::on_initialize() -> void {}

    auto system::on_finalize() -> void {}

    auto system::on_start() -> void {}

    auto system::on_stop() -> void {}

    auto system::on_update(time_step time) -> void {}
}
