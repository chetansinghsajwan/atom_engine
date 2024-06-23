export module atom.engine:ecs.entity_events;

import atom.core;
import :events;
import :ecs.entity;

namespace atom::engine
{
    enum class entity_event_type
    {
        create,
        destroy,
        component_add,
        component_remove,
    };

    export struct entity_event: public event_base
    {
        entity_event(entity_id entity, entity_event_type event_type)
            : entity{ entity }
            , event_type{ event_type }
        {}

        entity_id entity;
        entity_event_type event_type;
    };

    export struct entity_create_event: public entity_event
    {
        entity_create_event(entity_id entity)
            : entity_event{ entity, entity_event_type::create }
        {}
    };

    export struct entity_destroy_event: public entity_event
    {
        entity_destroy_event(entity_id entity)
            : entity_event{ entity, entity_event_type::destroy }
        {}
    };

    export struct entity_component_event: public entity_event
    {
        template <typename component_type>
        entity_component_event(entity_id entity, entity_event_type type, component_type* comp)
            : entity_event{ entity, type }
            , component_type_id{ type_info<component_type>::get_id() }
            , component{ comp }
        {}

        type_id component_type_id;
        void* component;
    };

    export struct entity_component_add_event: public entity_component_event
    {
        template <typename component_type>
        entity_component_add_event(entity_id entity, component_type* comp)
            : entity_component_event{ entity, entity_event_type::component_add, comp }
        {}
    };

    export struct entity_component_remove_event: public entity_component_event
    {
        template <typename component_type>
        entity_component_remove_event(entity_id entity, component_type* comp)
            : entity_component_event{ entity, entity_event_type::component_remove, comp }
        {}
    };

    export using entity_event_listener = event_listener<entity_event>;
}
