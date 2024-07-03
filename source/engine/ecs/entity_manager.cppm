export module atom.engine:ecs.entity_manager;

import entt;
import box2d;
import atom_core;
import :time;
import :events;
import :ecs.entity;
import :ecs.entity_events;
import :ecs.transform_component;

namespace atom::engine
{
    constexpr auto convert_atom_entity_id_to_entt_id(entity_id entity) -> entt::entity
    {
        return (entt::entity)entity;
    }

    constexpr auto convert_entt_entity_id_to_atom_id(entt::entity entity) -> entity_id
    {
        return (entity_id)entity;
    }

    export class world;

    /// --------------------------------------------------------------------------------------------
    ///
    /// --------------------------------------------------------------------------------------------
    export class entity_manager
    {
    public:
        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        entity_manager(class world* world);

        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        ~entity_manager();

    public:
        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        auto create_entity(string name) -> entity_id;

        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        auto destroy_entity(entity_id entity) -> void;

        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        auto get_name(entity_id entity) -> string_view;

        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        template <typename component_type, typename... arg_types>
        auto emplace_component(entity_id entity, arg_types&&... args) -> component_type*
        {
            entt::entity entt_entity = convert_atom_entity_id_to_entt_id(entity);
            component_type& component =
                _registry.emplace<component_type>(entt_entity, forward<arg_types>(args)...);

            entity_component_add_event event{ entity, &component };
            _event_source.dispatch(event);

            return &component;
        }

        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        template <typename component_type, typename... arg_types>
        auto get_or_emplace_component(entity_id entity, arg_types&&... args) -> component_type*
        {
            component_type* component =
                get_component<component_type>(entity, forward<arg_types>(args)...);

            if (component == nullptr)
            {
                component = emplace_component<component_type>(entity, forward<arg_types>(args)...);
            }

            return component;
        }

        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        template <typename component_type>
        auto remove_component(entity_id entity) -> void
        {
            entt::entity entt_entity = convert_atom_entity_id_to_entt_id(entity);

            component_type* component = _registry.try_get<component_type>(entt_entity);
            if (component != nullptr)
            {
                entity_component_remove_event event{ entity, component };
                _event_source.dispatch(event);
            }

            _registry.remove<component_type>(entt_entity);
        }

        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        template <typename component_type>
        auto get_component(entity_id entity) -> component_type*
        {
            entt::entity entt_entity = convert_atom_entity_id_to_entt_id(entity);
            return _registry.try_get<component_type>(entt_entity);
        }

        /// ----------------------------------------------------------------------------------------
        /// @todo make this count independent.
        /// ----------------------------------------------------------------------------------------
        template <typename component_type0, typename component_type1>
        auto find_one_with_components(
            entity_id* out_entity, component_type0** out_comp0, component_type1** out_comp1) -> bool
        {
            auto view = _registry.view<component_type0, component_type1>().each();
            for (auto [entt_entity, comp0, comp1] : view)
            {
                if (out_entity != nullptr)
                    *out_entity = convert_entt_entity_id_to_atom_id(entt_entity);

                if (out_comp0 != nullptr)
                    *out_comp0 = &comp0;

                if (out_comp1 != nullptr)
                    *out_comp1 = &comp1;

                return true;
            }

            return false;
        }

        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        template <typename... component_types, typename function_type>
        auto for_each_with_components(function_type&& func) -> void
        {
            return _registry.view<component_types...>().each(
                [&](entt::entity entt_entity, component_types&... components)
                {
                    entity_id entity = convert_entt_entity_id_to_atom_id(entt_entity);
                    func(entity, components...);
                });
        }

        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        auto get_world() -> world*;

        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        auto subscribe_events(entity_event_listener* listener) -> void;

        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        auto unsubscribe_events(entity_event_listener* listener) -> void;

    private:
        entt::registry _registry;
        world* _world;
        event_source<entity_event> _event_source;
    };
}
