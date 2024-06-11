export module atom.engine:ecs.entity_manager;

import entt;
import :box2d;
import atom.core;
import :time;
import :ecs.entity;
import :ecs.transform_component;

namespace atom::engine
{
    /// --------------------------------------------------------------------------------------------
    /// 
    /// --------------------------------------------------------------------------------------------
    export class entity_manager
    {
    public:
        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        entity_manager();

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
        auto update_entities(time_step time) -> void;

        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        auto view_all() -> decltype(auto);

        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        auto get_internal() -> entt::registry*;

    private:
        entt::registry _registry;
    };
}
