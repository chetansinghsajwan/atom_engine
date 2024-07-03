module atom_engine:ecs.box_collider2d_component.impl;

import atom_core;
import box2d;
import :math;
import :ecs.entity;
import :ecs.box_collider2d_component;
import :ecs.transform_component;
import :ecs.rigidbody_component;

namespace atom::engine
{
    box_collider2d_component::box_collider2d_component() = default;

    box_collider2d_component::box_collider2d_component(const this_type&) = default;
    box_collider2d_component& box_collider2d_component::operator=(const this_type&) = default;

    box_collider2d_component::box_collider2d_component(this_type&&) = default;
    box_collider2d_component& box_collider2d_component::operator=(this_type&&) = default;

    box_collider2d_component::~box_collider2d_component() = default;
}
