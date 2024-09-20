export module atom_engine:rendering.sprite;

import atom_core;
import :math;
import :rendering.texture2d;

namespace atom::engine
{
    export class sprite
    {
    public:
        sprite(texture2d* texture, f32vec2 min, f32vec2 max)
            : _texture(texture)
        {
            _coords[0] = { min.x, min.y };
            _coords[1] = { max.x, min.y };
            _coords[2] = { max.x, max.y };
            _coords[3] = { min.x, max.y };
        }

    public:
        static auto make_from_coords(texture2d* texture, f32vec2 coords, f32vec2 cell_size,
            f32vec2 sprite_size = f32vec2{ 1 }) -> sprite*
        {
            u32vec2 texture_size = texture->get_size();

            f32vec2 min = { (coords.x * cell_size.x) / texture_size.x,
                (coords.y * cell_size.y) / texture_size.y };

            f32vec2 max = { ((coords.x + sprite_size.x) * cell_size.x) / texture_size.x,
                ((coords.y + sprite_size.y) * cell_size.y) / texture_size.y };

            return new sprite{ texture, min, max };
        }

    public:
        auto get_texture() const -> texture2d*
        {
            return _texture;
        }

        auto get_texture_coords() const -> array_view<f32vec2>
        {
            return _coords;
        }

    private:
        texture2d* _texture;
        static_array<f32vec2, 4> _coords;
    };
}
