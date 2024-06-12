module atom.engine:ecs.entity_manager.impl;

import entt;
import atom.core;
import :box2d;
import :time;
import :ecs.entity;
import :ecs.transform_component;
import :ecs.entity_manager;
import :ecs.entity_events;

namespace atom::engine
{
    entity_manager::entity_manager(class world* world)
        : _world{ world }
    {}

    entity_manager::~entity_manager() {}

    auto entity_manager::create_entity(string_view name) -> entity*
    {
        entt::entity id = _registry.create();
        class entity* entity = &_registry.emplace<class entity>(id, id, &_registry, this, name);

        entity_create_event event{ id };
        _event_source.dispatch(event);

        emplace_component<transform_component>(id);

        return entity;
    }

    auto entity_manager::destroy_entity(class entity* entity) -> void
    {
        if (entity == nullptr)
        {
            return;
        }

        entity_destroy_event event{ entity->get_id() };
        _event_source.dispatch(event);

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

    auto entity_manager::subscribe_events(entity_event_listener* listener) -> void
    {
        _event_source.subscribe(listener);
    }

    auto entity_manager::unsubscribe_events(entity_event_listener* listener) -> void
    {
        _event_source.unsubscribe(listener);
    }
}
