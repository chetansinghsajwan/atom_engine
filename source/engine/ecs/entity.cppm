export module atom.engine:ecs.entity;

import entt;
import atom.core;
import :time;
import :ecs.entity_component;

namespace atom::engine
{
    export class entity_manager;
    
    export class entity
    {
    public:
        entity(entt::entity id, entt::registry* registry, entity_manager* manager, string_view name)
            : _id{ id }
            , _registry{ registry }
            , _manager{ manager }
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

            static_cast<entity_component*>(component)->on_attach(this);
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

        template <typename component_type>
        auto get_or_emplace_component() -> component_type*
            requires typeinfo<component_type>::is_pure
                     and (typeinfo<component_type>::template is_derived_from<entity_component>)
        {
            component_type* component = get_component<component_type>();
            if (component == nullptr)
            {
                component = emplace_component<component_type>();
            }

            return component;
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

        virtual auto on_update(time_step time) -> void
        {
            update_components(time);
        }

        auto update_components(time_step time) -> void
        {
            for (entity_component* component : _components)
            {
                component->on_update(time);
            }
        }

        auto get_manager() -> entity_manager*
        {
            return _manager;
        }

    public:
        entt::entity _id;
        entt::registry* _registry;
        string _name;
        entity_manager* _manager;
        buf_array<entity_component*, 10> _components;
    };
}
