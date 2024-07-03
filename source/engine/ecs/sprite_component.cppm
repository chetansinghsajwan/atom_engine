export module atom_engine:ecs.sprite_component;

import :math;
import :colors;
import :ecs.entity_component;
import :rendering.texture2d;

namespace atom::engine
{
    export class sprite_component: public entity_component
    {
    public:
        sprite_component();
        ~sprite_component();

    public:
        auto set_texture(texture2d* texture) -> void;
        auto get_texture() const -> texture2d*;

        auto set_color(const class color& color) -> void;
        auto get_color() const -> color;

    private:
        texture2d* _texture;
        color _color;
    };
}
