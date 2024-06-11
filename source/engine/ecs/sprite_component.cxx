module atom.engine:ecs.sprite_component.final;

import :math;
import :colors;
import :ecs.entity_component;
import :ecs.sprite_component;

namespace atom::engine
{
    sprite_component::sprite_component(class color color)
        : _color{ color }
    {}

    sprite_component::~sprite_component() {}

    auto sprite_component::get_color() const -> color
    {
        return _color;
    }

    auto sprite_component::set_color(const class color& color) -> void
    {
        _color = color;
    }
}
