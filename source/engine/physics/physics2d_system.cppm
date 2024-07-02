export module atom.engine:physics.physics2d_system;

import atom_core;
import atom_logging;
import :box2d;
import :ecs;
import :time;

namespace atom::engine
{
    export class world;

    export class physics2d_system
        : public system
        , public entity_event_listener
    {
        using base_type = system;

    public:
        physics2d_system(class world* world);

        ~physics2d_system();

    public:
        virtual auto on_initialize() -> void override;
        virtual auto on_finalize() -> void override;
        virtual auto on_update(time_step time) -> void override;
        virtual auto on_event(entity_event& event) -> void override;

    private:
        auto _process_body_before_step(
            entity_id entity, transform_component* transform, rigidbody_component* body) -> void;

        auto _process_body_after_step(
            entity_id entity, transform_component* transform, rigidbody_component* body) -> void;

        auto _on_component_add_event(entity_component_add_event& event) -> void;
        auto _on_component_remove_event(entity_component_remove_event& event) -> void;

        auto _on_component_add(entity_id entity, rigidbody_component* comp) -> void;
        auto _on_component_remove(entity_id entity, rigidbody_component* comp) -> void;

        auto _on_component_add(entity_id entity, box_collider2d_component* comp) -> void;
        auto _on_component_remove(entity_id entity, box_collider2d_component* comp) -> void;

        static constexpr auto _convert_atom_rigibody_to_box2d(
            rigidbody_component::body_type type) -> b2BodyType;

    public:
        logging::logger* _logger;
        entity_manager* _entity_manager;
        b2World* _b2_world;
    };
}
