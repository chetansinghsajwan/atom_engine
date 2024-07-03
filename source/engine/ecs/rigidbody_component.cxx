module atom.engine:ecs.rigidbody_component.impl;

import atom_core;
import box2d;
import :math;
import :time;
import :world;
import :ecs.entity;
import :ecs.entity_manager;
import :ecs.entity_component;
import :ecs.transform_component;
import :ecs.rigidbody_component;
import :ecs.system_manager;
import :physics.physics2d_system;

namespace atom::engine
{
    rigidbody_component::rigidbody_component() = default;

    rigidbody_component::rigidbody_component(const this_type&) = default;
    rigidbody_component& rigidbody_component::operator=(const this_type&) = default;

    rigidbody_component::rigidbody_component(this_type&&) = default;
    rigidbody_component& rigidbody_component::operator=(this_type&&) = default;

    rigidbody_component::~rigidbody_component() = default;

    constexpr auto _convert_atom_rigibody_to_box2d(
        rigidbody_component::body_type type) -> b2BodyType
    {
        switch (type)
        {
            case rigidbody_component::body_type::static_:   return b2_staticBody;
            case rigidbody_component::body_type::dynamic:   return b2_dynamicBody;
            case rigidbody_component::body_type::kinematic: return b2_kinematicBody;
        }

        contract_panic("invalid value");
    }

    auto rigidbody_component::set_type(body_type type) -> void
    {
        _body_type = type;
        _b2_body->SetType(_convert_atom_rigibody_to_box2d(type));
    }

    auto rigidbody_component::get_type() const -> body_type
    {
        return _body_type;
    }

    auto rigidbody_component::set_fixed_rotation(bool flag) -> void
    {
        _b2_body->SetFixedRotation(flag);
    }

    auto rigidbody_component::is_fixed_rotation() const -> bool
    {
        return _b2_body->IsFixedRotation();
    }
}
