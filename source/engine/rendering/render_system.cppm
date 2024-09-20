export module atom.engine:rendering.render_system;

import atom.core;
import atom.logging;
import :ecs;
import :time;

namespace atom::engine
{
    class world;

    export class render_system
        : public system
        , public entity_event_listener
    {
        using base_type = system;

    public:
        render_system(world* world);
        ~render_system();

    public:
        virtual auto on_initialize() -> void override;
        virtual auto on_finalize() -> void override;
        virtual auto on_update(time_step time) -> void override;

        virtual auto handle(entity_event& event) -> void override;

    private:
        auto _handle(entity_component_add_event& event) -> void;
        auto _handle(entity_component_remove_event& event) -> void;
        auto _on_camera_component_add(entity_id id, camera_component* comp) -> void;
        auto _on_camera_component_remove(entity_id id, camera_component* comp) -> void;
        auto _find_camera_component() -> void;

    public:
        logging::logger* _logger;
        entity_manager* _entity_manager;
        entity_id _camera_entity = null_entity;
        transform_component* _camera_transform_component;
        camera_component* _camera_component;
    };
}
