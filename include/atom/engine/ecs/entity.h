#pragma once
#include "entt/entt.hpp"
#include "atom/engine/ecs/entity_component.h"

namespace atom::engine
{
    class entity
    {
    public:
        entity(entt::entity id, entt::registry* registry)
            : _id{ id }
            , _registry{ registry }
        {}

    public:
        template <typename component_type, typename... arg_types>
        auto emplace_component(arg_types&&... args) -> component_type*
            requires typeinfo<component_type>::is_pure
                     and (typeinfo<component_type>::template is_derived_from<entity_component>)
                     and (typeinfo<component_type>::template is_constructible_from<arg_types...>)
        {
            component_type& component =
                _registry->emplace<component_type>(_id, forward<arg_types>(args)...);
            return &component;
        }

    public:
        entt::entity _id;
        entt::registry* _registry;
    };
}
