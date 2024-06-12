export module atom.engine:ecs.entity;

import entt;

namespace atom::engine
{
    export using entity_id = entt::entity;
    export constexpr entity_id null_entity = entt::null;
}
