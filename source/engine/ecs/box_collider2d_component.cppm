export module atom.engine:ecs.box_collider2d_component;

import atom.core;
import :box2d;
import :math;
import :ecs.entity_component;
import :ecs.transform_component;
import :ecs.rigidbody_component;

namespace atom::engine
{
    export class box_collider2d_component: public entity_component
    {
        using base_type = entity_component;
        using this_type = box_collider2d_component;

    public:
        box_collider2d_component() = default;

        box_collider2d_component(const this_type&) = default;
        box_collider2d_component& operator=(const this_type&) = default;

        box_collider2d_component(this_type&&) = default;
        box_collider2d_component& operator=(this_type&&) = default;

        ~box_collider2d_component() {}

    protected:
        virtual auto on_attach(class entity* entity) -> void override
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
            fixtureDef.restitutionThreshold = this->restitution_threshold;

            _fixture = body->CreateFixture(&fixtureDef);
        }

        virtual auto on_deattach() -> void override
        {
            base_type::on_deattach();

            b2Body* body = _fixture->GetBody();
            body->DestroyFixture(_fixture);
        }

    public:
        f32vec2 offset = f32vec2{ 0 };
        f32vec2 size = f32vec2{ .5 };

        f32 density = 1;
        f32 friction = .5;
        f32 restitution = 0;
        f32 restitution_threshold = .5;

    private:
        transform_component* _transform_component = nullptr;
        rigidbody_component* _rigidbody_component = nullptr;
        b2Fixture* _fixture = nullptr;
    };
}
