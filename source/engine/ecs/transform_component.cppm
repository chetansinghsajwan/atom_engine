export module atom.engine:ecs.transform_component;
import :ecs.entity_component;
import :math;

namespace atom::engine
{
    export class transform_component: public entity_component
    {
        using this_t = transform_component;

    public:
        transform_component(const this_t&) = default;
        transform_component& operator=(const this_t&) = default;

        transform_component(this_t&&) = default;
        transform_component& operator=(this_t&&) = default;

        transform_component(
            f32vec3 position = f32vec3{ 0 }, f32vec3 rotation = f32vec3{ 0 }, f32vec3 scale = f32vec3{ 1 })
            : _position{ position }
            , _rotation{ rotation }
            , _scale{ scale }
        {}

        ~transform_component() {}

    public:
        auto get_matrix() const -> f32mat4
        {
            f32mat4 transform = math::translate(f32mat4{ 1 }, _position)
                             * math::scale(f32mat4{ 1 }, f32vec3{ _scale.x, _scale.y, 1 });

            if (_rotation != f32vec3{ 0 })
            {
                f32mat4 rotation = math::rotate(f32mat4{ 1 }, _rotation.x, { 1, 0, 0 })
                                * math::rotate(f32mat4{ 1 }, _rotation.y, { 0, 1, 0 })
                                * math::rotate(f32mat4{ 1 }, _rotation.z, { 0, 0, 1 });

                transform *= rotation;
            }

            return transform;
        }

        auto set_position(f32vec3 position) -> void
        {
            _position = position;
        }

        auto get_position() const -> f32vec3
        {
            return _position;
        }

        auto set_rotation(f32vec3 rotation) -> void
        {
            _rotation = rotation;
        }

        auto get_rotation() const -> f32vec3
        {
            return _rotation;
        }

        auto set_scale(f32vec3 scale) -> void
        {
            _scale = scale;
        }

        auto get_scale() const -> f32vec3
        {
            return _scale;
        }

    private:
        f32vec3 _position = f32vec3{ 0 };
        f32vec3 _rotation = f32vec3{ 0 };
        f32vec3 _scale = f32vec3{ 1 };
    };
}
