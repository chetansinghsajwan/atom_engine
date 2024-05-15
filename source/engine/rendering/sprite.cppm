export module atom.engine:rendering.sprite;

import atom.core;
import :math;
import :rendering.texture2d;

namespace atom::engine
{
    export class sprite
    {
    public:
        sprite(texture2d* texture, vec2 min, vec2 max)
            : _texture(texture)
        {
            _coords[0] = vec2(min.x, min.y);
            _coords[1] = vec2(max.x, min.y);
            _coords[2] = vec2(max.x, max.y);
            _coords[3] = vec2(min.x, max.y);
        }

    public:
        static auto make_from_coords(texture2d* texture, vec2 coords, vec2 cell_size,
            vec2 sprite_size = vec2(1, 1)) -> sprite*
        {
            u32 texture_width = texture->get_width();
            u32 texture_height = texture->get_height();

            vec2 min = vec2((coords.x * cell_size.x) / texture_width,
                (coords.y * cell_size.y) / texture_height);

            vec2 max = vec2(((coords.x + sprite_size.x) * cell_size.x) / texture_width,
                ((coords.y + sprite_size.y) * cell_size.y) / texture_height);

            return new sprite(texture, min, max);
        }

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
