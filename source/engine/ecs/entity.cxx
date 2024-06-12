module atom.engine:ecs.entity.impl;

import entt;
import atom.core;
import :time;
import :ecs.entity_component;
import :ecs.entity;

namespace atom::engine
{
    entity::entity(
        entt::entity id, entt::registry* registry, entity_manager* manager, string_view name)
        : _id{ id }
        , _registry{ registry }
        , _manager{ manager }
        , _name{ name }
    {}

    entity::~entity() {}

    auto entity::get_id() const -> entt::entity
    {
        return _id;
    }

    auto entity::set_name(string name) -> void
    {
        _name = name;
    }

    auto entity::get_name() const -> string_view
    {
        return _name;
    }

    // auto entity::remove_component(entity_component* component) -> void
    // {
    //     std::cout << "remove component" << std::endl;
    // }

    // auto entity::get_all_components() -> array_slice<entity_component*>
    // {
    //     return _components;
    // }

    // auto entity::on_update(time_step time) -> void
    // {
    //     update_components(time);
    // }

    // auto entity::update_components(time_step time) -> void
    // {
    //     for (entity_component* component : _components)
    //     {
    //         component->on_update(time);
    //     }
    // }

    auto entity::get_manager() -> entity_manager*
    {
        return _manager;
    }
}
