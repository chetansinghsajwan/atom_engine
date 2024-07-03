export module atom.engine:ecs.entity;

import entt;
import atom_core;

namespace atom::engine
{
    export using entity_id = u32;
    export constexpr entity_id null_entity = (entity_id)entt::null;
}
