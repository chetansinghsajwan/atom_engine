export module atom.engine:physics.physics2d_system;

import atom.core;
import atom.logging;
import :box2d;
import :ecs;
import :time;

namespace atom::engine
{
    export class world;
    export class entity_manager;

    export class physics2d_system: public system
    {
        using base_type = system;

    public:
        physics2d_system(class world* world);

        ~physics2d_system();

    public:
        virtual auto on_initialize() -> void override;
        virtual auto on_update(time_step time) -> void override;
        virtual auto on_finalize() -> void override;

    private:
        auto _initialize_body(
            entt::entity entity, transform_component* transform, rigidbody_component* body) -> void;

        auto _finalize_body(
            entt::entity entity, transform_component* transform, rigidbody_component* body) -> void;

        auto _process_body_before_step(
            entt::entity entity, transform_component* transform, rigidbody_component* body) -> void;

        auto _process_body_after_step(
            entt::entity entity, transform_component* transform, rigidbody_component* body) -> void;

    public:
        logging::logger* _logger;
        entity_manager* _entity_manager;
        b2World* _b2_world;
    };
}
