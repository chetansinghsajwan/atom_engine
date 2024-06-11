export module atom.engine:ecs.sprite_component;

import :math;
import :colors;
import :ecs.entity_component;

namespace atom::engine
{
    export class sprite_component: public entity_component
    {
    public:
        sprite_component(class color color = colors::white);

        ~sprite_component();

    public:
        auto get_color() const -> color;

        auto set_color(const class color& color) -> void;

    private:
        color _color;
    };
}
