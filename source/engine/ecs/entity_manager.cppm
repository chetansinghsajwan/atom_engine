export module atom.engine:ecs.entity_manager;

import entt;
import :box2d;
import atom.core;
import :time;
import :events;
import :ecs.entity;
import :ecs.entity_events;
import :ecs.transform_component;

namespace atom::engine
{
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
        auto create_entity(string_view name) -> entity*;

        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        auto destroy_entity(class entity* entity) -> void;

        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        template <typename component_type, typename... arg_types>
        auto emplace_component(entity_id id, arg_types&&... args) -> component_type*
        {
            component_type& comp =
                _registry.emplace<component_type>(id, forward<arg_types>(args)...);

            entity_component_add_event event{ id, &comp };
            _event_source.dispatch(event);

            return &comp;
        }

        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        template <typename component_type, typename... arg_types>
        auto get_or_emplace_component(entity_id id, arg_types&&... args) -> component_type*
        {
            component_type* comp = get_component<component_type>();

            if (comp == nullptr)
            {
                comp = emplace_component<component_type>(id, forward<arg_types>(args)...);
            }

            return comp;
        }

        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        template <typename component_type>
        auto remove_component(entity_id id) -> void
        {
            component_type* comp = _registry.try_get<component_type>(id);
            if (comp != nullptr)
            {
                entity_component_remove_event event{ id, comp };
                _event_source.dispatch(event);
            }

            _registry.remove<component_type>();
        }

        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        template <typename component_type>
        auto get_component(entity_id id) -> component_type*
        {
            return _registry.try_get<component_type>(id);
        }

        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        auto view_all() -> decltype(auto);

        /// ----------------------------------------------------------------------------------------
        /// @todo make this count independent.
        /// ----------------------------------------------------------------------------------------
        template <typename component_type0, typename component_type1>
        auto find_one_with_components(
            entity_id* out_entity, component_type0** out_comp0, component_type1** out_comp1) -> bool
        {
            auto view = _registry.view<component_type0, component_type1>().each();
            for (auto [id, comp0, comp1] : view)
            {
                if (out_entity != nullptr)
                    *out_entity = id;

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
            return _registry.view<component_types...>().each(forward<function_type>(func));
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
