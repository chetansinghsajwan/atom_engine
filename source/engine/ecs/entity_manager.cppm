export module atom.engine:ecs.entity_manager;

import entt;
import atom.core;
import :ecs.entity;
import :ecs.transform_component;

namespace atom::engine
{
    export class entity_manager
    {
    public:
        entity_manager() {}

        ~entity_manager() {}

    public:
        auto create_entity(string_view name) -> entity*
        {
            entt::entity entt_id = _registry.create();
            class entity* entity =
                &_registry.emplace<class entity>(entt_id, entt_id, &_registry, name);

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

        auto view_all() -> decltype(auto)
        {
            return _registry.view<entity>().each();
        }

        auto get_internal() -> entt::registry*
        {
            return &_registry;
        }

    private:
        entt::registry _registry;
    };
}
