export module atom_engine:ecs.entity_component;

import :time;

namespace atom::engine
{
    export struct entity;

    export struct entity_component
    {
    public:
        entity_component();
        ~entity_component();
    };
}
