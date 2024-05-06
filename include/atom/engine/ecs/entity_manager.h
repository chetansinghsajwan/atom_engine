#pragma once
#include "entt/entt.hpp"
#include "atom/engine/ecs/entity.h"

namespace atom::engine
{
    class entity_manager
    {
    public:
        entity_manager() {}

        ~entity_manager() {}

    public:
        auto create_entity() -> entity*
        {
            entt::entity entt_id = _registry.create();
            return new entity(entt_id, &_registry);
        }

        auto destroy_entity(class entity* entity) -> void
        {
            if (entity == nullptr)
            {
                return;
            }

            delete entity;
        }

        auto get_internal() -> entt::registry*
        {
            return &_registry;
        }

    private:
        entt::registry _registry;
    };
}
