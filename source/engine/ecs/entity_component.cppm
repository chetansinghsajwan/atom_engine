export module atom.engine:ecs.entity_component;

namespace atom::engine
{
    export class entity;

    export class entity_component
    {
    public:
        auto get_entity() const -> entity*
        {
            return _entity;
        }

    public:
        virtual auto on_update() -> void {}

    private:
        entity* _entity;
    };
}
