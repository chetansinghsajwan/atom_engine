module atom.engine:ecs.entity_component.impl;

import :time;
import :ecs.entity_component;

namespace atom::engine
{
    entity_component::entity_component() {}

    entity_component::~entity_component() {}

    auto entity_component::get_entity() const -> entity*
    {
        return _entity;
    }

    auto entity_component::on_attach(class entity* entity) -> void
    {
        _entity = entity;
    }

    auto entity_component::on_update(time_step time) -> void {}

    auto entity_component::on_deattach() -> void
    {
        _entity = nullptr;
    }
}
