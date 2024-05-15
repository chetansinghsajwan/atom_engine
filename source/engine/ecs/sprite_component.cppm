export module atom.engine:ecs.sprite_component;

import :math;
import :ecs.entity_component;

namespace atom::engine
{
    export class sprite_component: public entity_component
    {
    public:
        sprite_component(vec4 color = vec4(1))
            : _color{ color }
        {}

        ~sprite_component() {}

    public:
        auto get_color() const -> vec4
        {
            return _color;
        }

    private:
        vec4 _color;
    };
}
