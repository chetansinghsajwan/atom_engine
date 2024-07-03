module atom_engine:ecs.transform_component.impl;

import :math;
import :ecs.entity_component;
import :ecs.transform_component;

namespace atom::engine
{
    transform_component::transform_component(const this_type&) = default;
    transform_component& transform_component::operator=(const this_type&) = default;

    transform_component::transform_component(this_type&&) = default;
    transform_component& transform_component::operator=(this_type&&) = default;

    transform_component::transform_component(f32vec3 position, f32vec3 rotation, f32vec3 scale)
        : _position{ position }
        , _rotation{ rotation }
        , _scale{ scale }
    {}

    transform_component::~transform_component() = default;

    auto transform_component::get_matrix() const -> f32mat4
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

    auto transform_component::set_position(f32vec3 position) -> void
    {
        _position = position;
    }

    auto transform_component::get_position() const -> f32vec3
    {
        return _position;
    }

    auto transform_component::set_rotation(f32vec3 rotation) -> void
    {
        _rotation = rotation;
    }

    auto transform_component::get_rotation() const -> f32vec3
    {
        return _rotation;
    }

    auto transform_component::set_scale(f32vec3 scale) -> void
    {
        _scale = scale;
    }

    auto transform_component::get_scale() const -> f32vec3
    {
        return _scale;
    }
}
