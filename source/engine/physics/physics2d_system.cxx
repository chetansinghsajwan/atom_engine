module atom.engine:physics.physics2d_system.impl;

import atom.core;
import atom.logging;
import :box2d;
import :time;
import :ecs;
import :world;
import :math;
import :physics.physics2d_system;

namespace atom::engine
{
    constexpr i32 velocity_iterations = 6;
    constexpr i32 position_iterations = 2;
    constexpr f32vec2 gravity = { 0, -9.8f };

    physics2d_system::physics2d_system(class world* world)
        : system{ "physics2d_system", world }
    {}

    physics2d_system::~physics2d_system() {}

    auto physics2d_system::on_initialize() -> void
    {
        _logger = logging::logger_manager::create_logger({ .name = "physics2d_system" })
                      .get_value_checked();

        _logger->log_info("initializing...");

        _entity_manager = get_world()->get_entity_manager();

        b2Vec2 b2_gravity = b2Vec2{ gravity.x, gravity.y };
        _b2_world = new b2World{ b2_gravity };

        _logger->log_info("initialization successfull.");
    }

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

    auto physics2d_system::_initialize_body(
        entity_id entity, transform_component* transform, rigidbody_component* body) -> void
    {
        f32vec3 position = transform->get_position();
        f32vec3 rotation = transform->get_rotation();
        f32vec3 scale = transform->get_scale();

        io::println("_initialize_body(): position: {}, {}", position.y, body->_body_type);

        b2BodyDef body_def;
        body_def.type = _convert_atom_rigibody_to_box2d(body->_body_type);
        body_def.position.Set(position.x, position.y);
        body_def.angle = rotation.z;

        b2Body* b2_body = _b2_world->CreateBody(&body_def);
        b2_body->SetFixedRotation(body->_fixed_rotation);

        b2PolygonShape box_shape;
        box_shape.SetAsBox(.5 * scale.x, .5 * scale.y);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &box_shape;
        fixtureDef.density = 1;
        fixtureDef.friction = .5;
        fixtureDef.restitution = 0;
        fixtureDef.restitutionThreshold = .5;

        b2Fixture* b2_fixture = b2_body->CreateFixture(&fixtureDef);

        body->_b2_body = b2_body;
    }

    auto physics2d_system::_finalize_body(
        entity_id entity, transform_component* transform, rigidbody_component* body) -> void
    {
        _b2_world->DestroyBody(body->_b2_body);
    }

    auto physics2d_system::_process_body_before_step(
        entity_id entity, transform_component* transform, rigidbody_component* body) -> void
    {
        if (body->_b2_body == nullptr)
        {
            _initialize_body(entity, transform, body);
            return;
        }

        f32vec3 position = transform->get_position();
        f32vec3 rotation = transform->get_rotation();

        io::println("_process_body_before_step(): position: {}", position.y);

        b2Vec2 b2_position = { position.x, position.y };
        float b2_rotation = rotation.z;

        body->_b2_body->SetTransform(b2_position, b2_rotation);
    }

    auto physics2d_system::_process_body_after_step(
        entity_id entity, transform_component* transform, rigidbody_component* body) -> void
    {
        const b2Vec2& b2_position = body->_b2_body->GetPosition();
        f32 b2_rotation = body->_b2_body->GetAngle();

        f32vec3 position{ 0 };
        f32vec3 rotation{ 0 };

        position.x = b2_position.x;
        position.y = b2_position.y;
        rotation.z = b2_rotation;

        io::println("_process_body_after_step(): position: {}", position.y);

        transform->set_position(position);
        transform->set_rotation(rotation);
    }

    auto physics2d_system::on_update(time_step time) -> void
    {
        base_type::on_update(time);

        io::println("----------------------------------------------------------------------------");

        // sync other values into box2d.
        _entity_manager->for_each_with_components<transform_component, rigidbody_component>(
            [&](entity_id entity, transform_component& transform, rigidbody_component& body)
            { _process_body_before_step(entity, &transform, &body); });

        // step box2d.
        _b2_world->Step(time.get_seconds(), velocity_iterations, position_iterations);

        // write box2d values into others.
        _entity_manager->for_each_with_components<transform_component, rigidbody_component>(
            [&](entity_id entity, transform_component& transform, rigidbody_component& body)
            { _process_body_after_step(entity, &transform, &body); });
    }

    auto physics2d_system::on_finalize() -> void
    {
        _logger->log_info("finalizing...");

        delete _b2_world;

        _logger->log_info("finalization successfull.");

        delete _logger;
    }
}
