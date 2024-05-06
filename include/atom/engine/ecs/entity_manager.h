#pragma once
#include "entt/entt.hpp"
#include "atom/engine/ecs/entity.h"
#include "atom/engine/ecs/transform_component.h"

namespace atom::engine
{
    class entity_manager
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
            _registry.emplace<transform_component>(entt_id);

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

        auto get_internal() -> entt::registry*
        {
            return &_registry;
        }

    private:
        entt::registry _registry;
    };
}
