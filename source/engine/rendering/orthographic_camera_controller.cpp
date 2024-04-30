#include "orthographic_camera_controller.h"

namespace atom::engine
{
    orthographic_camera_controller::orthographic_camera_controller(float aspect_ratio)
        : _aspect_ratio(aspect_ratio)
        , _position(0, 0, 0)
        , _rotation(0)
        , _move_speed(3)
        , _rotation_speed(140)
        , _zoom_level(1)
        , _camera(
              -_aspect_ratio * _zoom_level, _aspect_ratio * _zoom_level, -_zoom_level, _zoom_level)
    {}

    auto orthographic_camera_controller::on_update(time_stemp delta_time) -> void
    {
        if (_keyboard == nullptr)
            return;

        if (_keyboard->is_key_down(keyboard_key_code::w))
        {
            _position.y += _move_speed * delta_time.get_seconds();
        }

        if (_keyboard->is_key_down(keyboard_key_code::s))
        {
            _position.y -= _move_speed * delta_time.get_seconds();
        }

        if (_keyboard->is_key_down(keyboard_key_code::a))
        {
            _position.x -= _move_speed * delta_time.get_seconds();
        }

        if (_keyboard->is_key_down(keyboard_key_code::d))
        {
            _position.x += _move_speed * delta_time.get_seconds();
        }

        if (_keyboard->is_key_down(keyboard_key_code::q))
        {
            _position.z -= _move_speed * delta_time.get_seconds();
        }

        if (_keyboard->is_key_down(keyboard_key_code::e))
        {
            _position.z += _move_speed * delta_time.get_seconds();
        }

        if (_keyboard->is_key_down(keyboard_key_code::z))
        {
            _rotation += _rotation_speed * delta_time.get_seconds();
        }

        if (_keyboard->is_key_down(keyboard_key_code::x))
        {
            _rotation -= _rotation_speed * delta_time.get_seconds();
        }

        _camera.set_position(_position);
        _camera.set_rotation(_rotation);
    }

    auto orthographic_camera_controller::set_keyboard(class keyboard* keyboard) -> void
    {
        _keyboard = keyboard;
    }

    auto orthographic_camera_controller::_on_window_event(const window_event& event) -> void
    {
        switch (event.event_type)
        {
            case window_event_type::resize:
                _on_window_resize_event(reinterpret_cast<const window_resize_event&>(event));
                break;

            default: break;
        }
    }

    auto orthographic_camera_controller::_on_window_resize_event(
        const window_resize_event& event) -> void
    {
        _aspect_ratio = (float)event.size.x / (float)event.size.y;
        _camera.set_projection(
            -_aspect_ratio * _zoom_level, _aspect_ratio * _zoom_level, -_zoom_level, _zoom_level);
    }

    auto orthographic_camera_controller::_on_mouse_event(const mouse_event& event) -> void
    {
        switch (event.event_type)
        {
            case mouse_event_type::scroll_event:
                _on_mouse_scroll_event(reinterpret_cast<const mouse_scroll_event&>(event));
                break;

            default: break;
        }
    }

    auto orthographic_camera_controller::_on_mouse_scroll_event(
        const mouse_scroll_event& event) -> void
    {
        _zoom_level += event.yoffset.to_unwrapped<float>();
        _camera.set_projection(
            -_aspect_ratio * _zoom_level, _aspect_ratio * _zoom_level, -_zoom_level, _zoom_level);
    }
}
