module atom.engine:ecs.sprite_component.final;

import :math;
import :colors;
import :ecs.entity_component;
import :ecs.sprite_component;
import :rendering.texture2d;

namespace atom::engine
{
    sprite_component::sprite_component()
        : _texture{ nullptr }
        , _color{ colors::white }
    {}

    sprite_component::~sprite_component() {}

    auto sprite_component::set_texture(texture2d* texture) -> void
    {
        _texture = texture;
    }

    auto sprite_component::get_texture() const -> texture2d*
    {
        return _texture;
    }

    auto sprite_component::set_color(const class color& color) -> void
    {
        _color = color;
    }

    auto sprite_component::get_color() const -> color
    {
        return _color;
    }
}
