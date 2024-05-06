#pragma once
#include "atom/engine/rendering/texture2d.h"

namespace atom::engine
{
    class sprite
    {
    public:
        sprite(texture2d* texture, vec2 min, vec2 max);

    public:
        static auto make_from_coords(texture2d* texture, vec2 coords, vec2 cell_size, vec2 sprite_size = vec2(1, 1)) -> sprite*;

    public:
        auto get_texture() const -> texture2d*
        {
            return _texture;
        }

        auto get_texture_coords() const -> array_view<vec2>
        {
            return _coords;
        }

    private:
        texture2d* _texture;
        static_array<vec2, 4> _coords;
    };
}
