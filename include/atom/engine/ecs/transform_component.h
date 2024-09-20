#pragma once
#include "atom/engine/ecs/entity_component.h"
#include "atom/engine/math.h"

namespace atom::engine
{
    class transform_component: public entity_component
    {
        using this_t = transform_component;

    public:
        transform_component()
            : _transform(1)
        {}

        transform_component(const this_t&) = default;
        transform_component& operator=(const this_t&) = default;

        transform_component(this_t&&) = default;
        transform_component& operator=(this_t&&) = default;

        ~transform_component() {}

    public:
        auto get_matrix() const -> const mat4&
        {
            return _transform;
        }
    
        auto set_position(vec3 position) -> void
        {
            ATOM_PANIC("not implemented.");
        }

        auto get_position() const -> vec3
        {
            ATOM_PANIC("not implemented.");
            return vec3(0, 0, 0);
        }

        auto set_rotation(vec3 rotation) -> void
        {
            ATOM_PANIC("not implemented.");
        }

        auto get_rotation() const -> vec3
        {
            ATOM_PANIC("not implemented.");
            return vec3(0, 0, 0);
        }

        auto set_scale(vec3 scale) -> void
        {
            ATOM_PANIC("not implemented.");
        }

        auto get_scale() const -> vec3
        {
            ATOM_PANIC("not implemented.");
            return vec3(0, 0, 0);
        }

    private:
        mat4 _transform;
    };
}
