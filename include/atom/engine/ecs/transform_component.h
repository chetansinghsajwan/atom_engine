#pragma once
#include "atom/engine/ecs/entity_component.h"
#include "atom/engine/math.h"

namespace atom::engine
{
    class transform_component: public entity_component
    {
        using this_t = transform_component;

    public:
        transform_component(const this_t&) = default;
        transform_component& operator=(const this_t&) = default;

        transform_component(this_t&&) = default;
        transform_component& operator=(this_t&&) = default;

        transform_component(
            vec3 position = { 0, 0, 0 }, vec3 rotation = { 0, 0, 0 }, vec3 scale = { 1, 1, 1 })
            : _position{ position }
            , _rotation{ rotation }
            , _scale{ scale }
        {}

        ~transform_component() {}

    public:
        auto get_matrix() const -> mat4
        {
            mat4 transform = math::translate(mat4(1), _position)
                             * math::scale(mat4(1), vec3(_scale.x, _scale.y, 1));

            if (_rotation != vec3{ 0, 0, 0 })
            {
                mat4 rotation = math::rotate(mat4(1), _rotation.x, { 1, 0, 0 })
                                * math::rotate(mat4(1), _rotation.y, { 0, 1, 0 })
                                * math::rotate(mat4(1), _rotation.z, { 0, 0, 1 });

                transform *= rotation;
            }

            return transform;
        }

        auto set_position(vec3 position) -> void
        {
            _position = position;
        }

        auto get_position() const -> vec3
        {
            return _position;
        }

        auto set_rotation(vec3 rotation) -> void
        {
            _rotation = rotation;
        }

        auto get_rotation() const -> vec3
        {
            return _rotation;
        }

        auto set_scale(vec3 scale) -> void
        {
            _scale = scale;
        }

        auto get_scale() const -> vec3
        {
            return _scale;
        }

    private:
        vec3 _position = { 0, 0, 0 };
        vec3 _rotation = { 0, 0, 0 };
        vec3 _scale = { 1, 1, 1 };
    };
}
