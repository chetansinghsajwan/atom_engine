export module atom.engine:ecs.rigidbody_component;

import atom.core;
import :box2d;
import :math;
import :time;
import :ecs.entity;
import :ecs.entity_manager;
import :ecs.entity_component;
import :ecs.transform_component;

namespace atom::engine
{
    export class rigidbody_component: public entity_component
    {
        using base_type = entity_component;
        using this_type = rigidbody_component;

    public:
        enum class body_type : byte
        {
            static_,
            dynamic,
            kinematic
        };

    public:
        rigidbody_component() = default;

        rigidbody_component(const this_type&) = default;
        rigidbody_component& operator=(const this_type&) = default;

        rigidbody_component(this_type&&) = default;
        rigidbody_component& operator=(this_type&&) = default;

        virtual ~rigidbody_component() {}

    public:
        auto set_type(body_type type) -> void
        {
            _body_type = type;
            _physics_body->SetType(_convert_atom_rigibody_type_to_box2d(type));
        }

        auto get_type() const -> body_type
        {
            return _body_type;
        }

        auto set_fixed_rotation(bool flag) -> void
        {
            _fixed_rotation = flag;
            _physics_body->SetFixedRotation(flag);
        }

        auto get_fixed_rotation() const -> bool
        {
            return _fixed_rotation;
        }

        virtual auto on_attach(class entity* entity) -> void override
        {
            base_type::on_attach(entity);

            _transform_component = get_entity()->get_or_emplace_component<transform_component>();

            vec3 position = _transform_component->get_position();
            vec3 rotation = _transform_component->get_rotation();

            b2BodyDef body_def;
            body_def.type = _convert_atom_rigibody_type_to_box2d(_body_type);
            body_def.position.Set(position.x, position.y);
            body_def.angle = rotation.z;

            _physics_world = get_entity()->get_manager()->_get_physics_world();
            _physics_body = _physics_world->CreateBody(&body_def);
            _physics_body->SetFixedRotation(_fixed_rotation);
        }

        virtual auto on_update(time_step time) -> void override
        {
            base_type::on_update(time);

            constexpr i32 velocity_iterations = 6;
            constexpr i32 position_iterations = 2;

            _physics_world->Step(time.get_seconds(), velocity_iterations, position_iterations);

            const b2Vec2& physics_position = _physics_body->GetPosition();
            float physics_rotation = _physics_body->GetAngle();

            vec3 position = _transform_component->get_position();
            vec3 rotation = _transform_component->get_rotation();

            position.x = physics_position.x;
            position.y = physics_position.y;
            rotation.z = physics_rotation;

            _transform_component->set_position(position);
            _transform_component->set_rotation(rotation);
        }

        virtual auto on_deattach() -> void override
        {
            base_type::on_deattach();

            _physics_world->DestroyBody(_physics_body);
        }

        auto _get_body() -> b2Body*
        {
            return _physics_body;
        }

    private:
        constexpr auto _convert_atom_rigibody_type_to_box2d(body_type type) -> b2BodyType
        {
            switch (type)
            {
                case body_type::static_:   return b2_staticBody;
                case body_type::dynamic:   return b2_dynamicBody;
                case body_type::kinematic: return b2_kinematicBody;
            }

            contract_panic("invalid value");
        }

    private:
        transform_component* _transform_component = nullptr;

        body_type _body_type = body_type::static_;
        bool _fixed_rotation = false;

        b2World* _physics_world = nullptr;
        b2Body* _physics_body = nullptr;
    };
}
