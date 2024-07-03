module atom_engine:ecs.entity_manager.impl;

import entt;
import atom_core;
import box2d;
import :time;
import :ecs.entity;
import :ecs.transform_component;
import :ecs.entity_manager;
import :ecs.entity_events;

namespace atom::engine
{
    struct entity_data
    {
        string name;
    };

    entity_manager::entity_manager(class world* world)
        : _world{ world }
    {}

    entity_manager::~entity_manager() {}

    auto entity_manager::create_entity(string name) -> entity_id
    {
        entt::entity entt_entity = _registry.create();
        _registry.emplace<entity_data>(entt_entity, move(name));

        entity_id entity = convert_entt_entity_id_to_atom_id(entt_entity);
        entity_create_event event{ entity };
        _event_source.dispatch(event);

        emplace_component<transform_component>(entity);

        return entity;
    }

    auto entity_manager::destroy_entity(entity_id entity) -> void
    {
        contract_debug_expects(entity != null_entity);

        entity_destroy_event event{ entity };
        _event_source.dispatch(event);

        entt::entity entt_entity = convert_atom_entity_id_to_entt_id(entity);
        _registry.destroy(entt_entity);
    }

    auto entity_manager::get_name(entity_id entity) -> string_view
    {
        entt::entity entt_entity = convert_atom_entity_id_to_entt_id(entity);
        return _registry.get<entity_data>(entt_entity).name;
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
