export module atom.engine:ecs.entity_manager;

import entt;
import :box2d;
import atom.core;
import :time;
import :ecs.entity;
import :ecs.transform_component;

namespace atom::engine
{
    export class scene;

    export class entity_manager
    {
    public:
        entity_manager(class scene* scene, b2World* physics_world)
            : _scene{ scene }
            , _physics_world{ physics_world }
        {}

        ~entity_manager() {}

    public:
        auto create_entity(string_view name) -> entity*
        {
            entt::entity entt_id = _registry.create();
            class entity* entity =
                &_registry.emplace<class entity>(entt_id, entt_id, &_registry, this, name);

            entity->emplace_component<transform_component>();
            return entity;
        }

        auto destroy_entity(class entity* entity) -> void
        {
            if (entity == nullptr)
            {
                return;
            }

            _registry.destroy(entity->get_id());
        }

        auto update_entities(time_step time) -> void
        {
            auto view = _registry.view<entity>().each();
            for (auto [id, entity] : view)
            {
                entity.on_update(time);
            }
        }

        auto view_all() -> decltype(auto)
        {
            return _registry.view<entity>().each();
        }

        auto get_internal() -> entt::registry*
        {
            return &_registry;
        }

        auto get_scene() -> scene*
        {
            return _scene;
        }

        auto _get_physics_world() -> b2World*
        {
            return _physics_world;
        }

    private:
        entt::registry _registry;
        scene* _scene;
        b2World* _physics_world;
    };
}
