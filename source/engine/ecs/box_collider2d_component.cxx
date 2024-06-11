module atom.engine:ecs.box_collider2d_component.impl;

import atom.core;
import :box2d;
import :math;
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

    auto box_collider2d_component::on_attach(entity* entity) -> void
    {
        base_type::on_attach(entity);

        _transform_component = get_entity()->get_or_emplace_component<transform_component>();
        _rigidbody_component = get_entity()->get_or_emplace_component<rigidbody_component>();
        f32vec3 scale = _transform_component->get_scale();
        f32vec3 rotation = _transform_component->get_rotation();
        b2Body* body = _rigidbody_component->_get_body();

        b2PolygonShape box_shape;
        box_shape.SetAsBox(this->size.x * scale.x, this->size.y * scale.y);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &box_shape;
        fixtureDef.density = this->density;
        fixtureDef.friction = this->friction;
        fixtureDef.restitution = this->restitution;
        fixtureDef.restitutionThreshold = this->restitution_typehreshold;

        _fixture = body->CreateFixture(&fixtureDef);
    }

    auto box_collider2d_component::on_deattach() -> void
    {
        base_type::on_deattach();

        b2Body* body = _fixture->GetBody();
        body->DestroyFixture(_fixture);
    }
}
