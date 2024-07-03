export module atom.engine:ecs.box_collider2d_component;

import atom_core;
import box2d;
import :math;
import :ecs.entity_component;
import :ecs.transform_component;
import :ecs.rigidbody_component;

namespace atom::engine
{
    export class box_collider2d_component: public entity_component
    {
        friend class physics2d_system;

        using base_type = entity_component;
        using this_type = box_collider2d_component;

    public:
        box_collider2d_component();

        box_collider2d_component(const this_type&);
        box_collider2d_component& operator=(const this_type&);

        box_collider2d_component(this_type&&);
        box_collider2d_component& operator=(this_type&&);

        ~box_collider2d_component();

    public:
        f32vec2 offset = f32vec2{ 0 };
        f32vec2 size = f32vec2{ .5 };

        f32 density = 1;
        f32 friction = .5;
        f32 restitution = 0;
        f32 restitution_thresold = .5;

    private:
        b2Fixture* _b2_fixture = nullptr;
    };
}
