module atom.engine:rendering.render_system.impl;

import atom.core;
import atom.logging;
import :math;
import :ecs;
import :world;
import :time;
import :gui;
import :colors;
import :rendering.render_system;
import :rendering.renderer2d;
import :rendering.scene_camera;
import :rendering.frame_buffer;
import :rendering.render_command;

namespace atom::engine
{
    render_system::render_system(world* world)
        : base_type{ "render_system", world }
    {}

    render_system::~render_system() {}

    auto render_system::on_initialize() -> void
    {
        _logger =
            logging::logger_manager::create_logger({ .name = "render_system" }).get_value_checked();

        _logger->log_info("initializing...");

        _entity_manager = get_world()->get_entity_manager();
        _entity_manager->subscribe_events(this);

        _find_camera_component();

        render_command::set_clear_color(_screen_clear_color);

        _logger->log_info("initializing done.");
    }

    auto render_system::on_finalize() -> void
    {
        _logger->log_info("finalizing...");

        _entity_manager->unsubscribe_events(this);

        _logger->log_info("finalizing done.");
    }

    auto _render_spirte(
        entity_id entity, transform_component* transform, sprite_component* sprite) -> void
    {
        if (sprite->get_texture() == nullptr)
        {
            renderer2d::draw_quad(transform->get_matrix(), sprite->get_color());
        }
        else
        {
            renderer2d::draw_texture(
                transform->get_matrix(), sprite->get_texture(), 1, sprite->get_color());
        }
    }

    auto render_system::on_update(time_step time) -> void
    {
        renderer2d::reset_stats();

        render_command::clear_color();

        _camera_component->get_camera().set_viewport_size(1920, 1080);

        if (_camera_entity != null_entity)
        {
            scene_camera& camera = _camera_component->get_camera();
            const f32mat4& camera_transform = _camera_transform_component->get_matrix();

            renderer2d::begin_scene(&camera, camera_transform);

            _entity_manager->for_each_with_components<transform_component, sprite_component>(
                [&](entity_id entity, transform_component& transform, sprite_component& sprite)
                { _render_spirte(entity, &transform, &sprite); });

            renderer2d::draw_text("hello", f32mat4{ 2 });

            renderer2d::end_scene();
        }
    }

    auto render_system::on_event(entity_event& event) -> void
    {
        switch (event.event_type)
        {
            case entity_event_type::component_add:
            {
                _handle(reinterpret_cast<entity_component_add_event&>(event));
                break;
            }
            case entity_event_type::component_remove:
            {
                _handle(reinterpret_cast<entity_component_remove_event&>(event));
                break;
            }
            default: break;
        }
    }

    auto render_system::_handle(entity_component_add_event& event) -> void
    {
        if (event.component_type_id == type_info<camera_component>::get_id())
        {
            _on_camera_component_add(
                event.entity, reinterpret_cast<camera_component*>(event.component));
        }
    }

    auto render_system::_handle(entity_component_remove_event& event) -> void
    {
        if (event.component_type_id == type_info<camera_component>::get_id())
        {
            _on_camera_component_remove(
                event.entity, reinterpret_cast<camera_component*>(event.component));
        }
    }

    auto render_system::_on_camera_component_add(
        entity_id entity, camera_component* component) -> void
    {
        _logger->log_info("new camera component found with entity_id '{}'.", entity);

        if (_camera_entity != null_entity)
        {
            return;
        }

        _logger->log_info("selecting new camera component with entity_id '{}'.", entity);

        _camera_entity = entity;
        _camera_component = component;
        _camera_transform_component = _entity_manager->get_component<transform_component>(entity);
    }

    auto render_system::_on_camera_component_remove(
        entity_id entity, camera_component* component) -> void
    {
        if (_camera_entity == entity)
        {
            _logger->log_info(
                "currently selected camera component removed with entity_id '{}'.", entity);

            _find_camera_component();
        }
    }

    auto render_system::_find_camera_component() -> void
    {
        _logger->log_info("searching for camera...");

        bool found =
            _entity_manager->find_one_with_components<transform_component, camera_component>(
                &_camera_entity, &_camera_transform_component, &_camera_component);

        if (found)
        {
            _logger->log_info(
                "searching for camera done, selected with entity_id '{}'", _camera_entity);
        }
        else
        {
            _logger->log_info("searching for camera done, no camera found.");

            _camera_entity = null_entity;
            _camera_component = nullptr;
            _camera_transform_component = nullptr;
        }
    }
}
