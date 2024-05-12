#pragma once
#include "atom.core.h"
#include "entt/entt.hpp"
#include "atom/engine/ecs/entity_component.h"

namespace atom::engine
{
    class entity
    {
    public:
        entity(entt::entity id, entt::registry* registry, string_view name)
            : _id{ id }
            , _registry{ registry }
            , _name{ name }
        {}

    public:
        auto get_id() const -> entt::entity
        {
            return _id;
        }

        auto set_name(string name) -> void
        {
            _name = name;
        }

        auto get_name() const -> string_view
        {
            return _name;
        }

        template <typename component_type, typename... arg_types>
        auto emplace_component(arg_types&&... args) -> component_type*
            requires typeinfo<component_type>::is_pure
                     and (typeinfo<component_type>::template is_derived_from<entity_component>)
                     and (typeinfo<component_type>::template is_constructible_from<arg_types...>)
        {
            component_type* component =
                &_registry->emplace<component_type>(_id, forward<arg_types>(args)...);

            _components.emplace_back(component);
            return component;
        }

        auto remove_component(entity_component* component) -> void
        {
            std::cout << "remove component" << std::endl;
        }

        template <typename component_type>
        auto get_component() -> component_type*
            requires typeinfo<component_type>::is_pure
                     and (typeinfo<component_type>::template is_derived_from<entity_component>)
        {
            return _registry->try_get<component_type>(_id);
        }

        auto get_all_components() -> array_slice<entity_component*>
        {
            return _components;
        }

        template <typename component_type>
        auto has_component() -> bool
            requires typeinfo<component_type>::is_pure
                     and (typeinfo<component_type>::template is_derived_from<entity_component>)
        {
            return _registry->try_get<component_type>(_id) != nullptr;
        }

    public:
        entt::entity _id;
        entt::registry* _registry;
        string _name;
        buf_array<entity_component*, 10> _components;
    };
}
