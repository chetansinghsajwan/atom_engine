module atom.engine:ecs.entity_manager.impl;

import entt;
import atom.core;
import :box2d;
import :time;
import :ecs.entity;
import :ecs.transform_component;
import :ecs.entity_manager;

namespace atom::engine
{
    entity_manager::entity_manager(class world* world)
        : _world{ world }
    {}

    entity_manager::~entity_manager() {}

    auto entity_manager::create_entity(string_view name) -> entity*
    {
        entt::entity entt_id = _registry.create();
        class entity* entity =
            &_registry.emplace<class entity>(entt_id, entt_id, &_registry, this, name);

        entity->emplace_component<transform_component>();
        return entity;
    }

    auto entity_manager::destroy_entity(class entity* entity) -> void
    {
        if (entity == nullptr)
        {
            return;
        }

        _registry.destroy(entity->get_id());
    }

    auto entity_manager::view_all() -> decltype(auto)
    {
        return _registry.view<entity>().each();
    }

    auto entity_manager::get_world() -> world*
    {
        return _world;
    }

    auto entity_manager::get_internal() -> entt::registry*
    {
        return &_registry;
    }
}
