export module atom.engine:ecs.entity_component;

import :time;

namespace atom::engine
{
    export class entity;

    export class entity_component
    {
    public:
        entity_component() {}

        virtual ~entity_component() {}

    public:
        auto get_entity() const -> entity*
        {
            return _entity;
        }

    public:
        virtual auto on_attach(class entity* entity) -> void
        {
            _entity = entity;
        }

        virtual auto on_update(time_step time) -> void {}

        virtual auto on_deattach() -> void
        {
            _entity = nullptr;
        }

    private:
        entity* _entity;
    };
}
