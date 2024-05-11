#pragma once

namespace atom::engine
{
    class entity;

    class entity_component
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
