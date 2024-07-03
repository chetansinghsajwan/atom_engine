module atom_engine:physics.physics2d_system.impl;

import atom_core;
import atom_logging;
import box2d;
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
        _entity_manager->subscribe_events(this);

        b2Vec2 b2_gravity = b2Vec2{ gravity.x, gravity.y };
        _b2_world = new b2World{ b2_gravity };

        _logger->log_info("initialization successfull.");
    }

    auto physics2d_system::on_finalize() -> void
    {
        _logger->log_info("finalizing...");

        _entity_manager->unsubscribe_events(this);
        delete _b2_world;

        _logger->log_info("finalization successfull.");

        delete _logger;
    }

    auto physics2d_system::on_update(time_step time) -> void
    {
        base_type::on_update(time);

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

    auto physics2d_system::on_event(entity_event& event) -> void
    {
        switch (event.event_type)
        {
            case entity_event_type::component_add:
            {
                _on_component_add_event(reinterpret_cast<entity_component_add_event&>(event));
                break;
            }

            case entity_event_type::component_remove:
            {
                _on_component_remove_event(reinterpret_cast<entity_component_remove_event&>(event));
                break;
            }

            default: break;
        }
    }

    auto physics2d_system::_process_body_before_step(
        entity_id entity, transform_component* transform, rigidbody_component* body) -> void
    {
        f32vec3 position = transform->get_position();
        f32vec3 rotation = transform->get_rotation();

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

        transform->set_position(position);
        transform->set_rotation(rotation);
    }

    auto physics2d_system::_on_component_add_event(entity_component_add_event& event) -> void
    {
        if (event.component_type_id == type_info<rigidbody_component>::get_id())
        {
            rigidbody_component* comp = reinterpret_cast<rigidbody_component*>(event.component);
            _on_component_add(event.entity, comp);
            return;
        }

        if (event.component_type_id == type_info<box_collider2d_component>::get_id())
        {
            box_collider2d_component* comp =
                reinterpret_cast<box_collider2d_component*>(event.component);
            _on_component_add(event.entity, comp);
            return;
        }
    }

    auto physics2d_system::_on_component_remove_event(entity_component_remove_event& event) -> void
    {
        if (event.component_type_id == type_info<rigidbody_component>::get_id())
        {
            rigidbody_component* comp = reinterpret_cast<rigidbody_component*>(event.component);
            _on_component_remove(event.entity, comp);
            return;
        }

        if (event.component_type_id == type_info<box_collider2d_component>::get_id())
        {
            box_collider2d_component* comp =
                reinterpret_cast<box_collider2d_component*>(event.component);
            _on_component_remove(event.entity, comp);
            return;
        }
    }

    auto physics2d_system::_on_component_add(entity_id entity, rigidbody_component* body) -> void
    {
        transform_component* transform =
            _entity_manager->get_component<transform_component>(entity);

        f32vec3 position = transform->get_position();
        f32vec3 rotation = transform->get_rotation();

        b2BodyDef body_def;
        body_def.position.Set(position.x, position.y);
        body_def.angle = rotation.z;

        b2Body* b2_body = _b2_world->CreateBody(&body_def);
        body->_b2_body = b2_body;
    }

    auto physics2d_system::_on_component_remove(entity_id entity, rigidbody_component* body) -> void
    {
        _b2_world->DestroyBody(body->_b2_body);
    }

    auto physics2d_system::_on_component_add(
        entity_id entity, box_collider2d_component* collider) -> void
    {
        rigidbody_component* body =
            _entity_manager->get_or_emplace_component<rigidbody_component>(entity);

        transform_component* transform =
            _entity_manager->get_or_emplace_component<transform_component>(entity);

        f32vec2 size = collider->size;
        f32vec2 scale = transform->get_scale();

        b2PolygonShape box_shape;
        box_shape.SetAsBox(size.x * scale.x, size.y * scale.y);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &box_shape;
        fixtureDef.density = collider->density;
        fixtureDef.friction = collider->friction;
        fixtureDef.restitution = collider->restitution;
        fixtureDef.restitutionThreshold = collider->restitution_thresold;

        b2Body* b2_body = body->_b2_body;
        b2Fixture* b2_fixture = b2_body->CreateFixture(&fixtureDef);

        collider->_b2_fixture = b2_fixture;
    }

    auto physics2d_system::_on_component_remove(
        entity_id entity, box_collider2d_component* collider) -> void
    {
        rigidbody_component* body = _entity_manager->get_component<rigidbody_component>(entity);
        b2Body* b2_body = body->_b2_body;

        b2_body->DestroyFixture(collider->_b2_fixture);
    }

    constexpr auto physics2d_system::_convert_atom_rigibody_to_box2d(
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
}
