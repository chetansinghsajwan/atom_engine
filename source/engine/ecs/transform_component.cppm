export module atom_engine:ecs.transform_component;

import :math;
import :ecs.entity_component;

namespace atom::engine
{
    export class transform_component: public entity_component
    {
        using this_type = transform_component;

    public:
        transform_component(const this_type&);
        transform_component& operator=(const this_type&);

        transform_component(this_type&&);
        transform_component& operator=(this_type&&);

        transform_component(f32vec3 position = f32vec3{ 0 }, f32vec3 rotation = f32vec3{ 0 },
            f32vec3 scale = f32vec3{ 1 });

        ~transform_component();

    public:
        auto get_matrix() const -> f32mat4;

        auto set_position(f32vec3 position) -> void;

        auto get_position() const -> f32vec3;

        auto set_rotation(f32vec3 rotation) -> void;

        auto get_rotation() const -> f32vec3;

        auto set_scale(f32vec3 scale) -> void;

        auto get_scale() const -> f32vec3;

    private:
        f32vec3 _position = f32vec3{ 0 };
        f32vec3 _rotation = f32vec3{ 0 };
        f32vec3 _scale = f32vec3{ 1 };
    };
}
