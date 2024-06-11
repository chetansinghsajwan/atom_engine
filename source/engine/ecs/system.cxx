module atom.engine:ecs.system.impl;

import atom.core;
import :time;
import :ecs.system;

namespace atom::engine
{
    system::system(string name)
        : _name{ move(name) }
    {}

    system::~system() {}

    auto system::get_name() const -> string_view
    {
        return _name;
    }

    auto system::on_start() -> void {}

    auto system::on_update(time_step time) -> void {}

    auto system::on_stop() -> void {}
}
