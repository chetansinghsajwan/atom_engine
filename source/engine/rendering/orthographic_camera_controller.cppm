export module atom.engine:rendering.orthographic_camera_controller;

import atom.core;
import :windows;
import :inputs;
import :time;
import :math;
import :rendering.orthographic_camera;

namespace atom::engine
{
    // @todo remove this export.
    export class orthographic_camera_controller
        : public window_event_listener
        , mouse_event_listener
    {
    public:
        orthographic_camera_controller(float aspect_ratio)
            : _aspect_ratio(aspect_ratio)
            , _position(0, 0, 0)
            , _rotation(0)
            , _zoom_speed(0.25f)
            , _move_speed(3)
            , _rotation_speed(140)
            , _zoom_level(1)
            , _camera(-_aspect_ratio * _zoom_level, _aspect_ratio * _zoom_level, -_zoom_level,
                  _zoom_level)
        {}

    public:
        auto on_update(time_step delta_time) -> void
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

        auto set_window(class window* window) -> void
        {
            _window = window;
            _window->subscribe_event(this);
        }

        auto set_keyboard(class keyboard* keyboard) -> void
        {
            _keyboard = keyboard;
        }

        auto set_mouse(class mouse* mouse) -> void
        {
            _mouse = mouse;
            _mouse->subscribe_event(this);
        }

        auto on_resize(vec2 size) -> void
        {
            _aspect_ratio = size.x / size.y;
            _camera.set_projection(-_aspect_ratio * _zoom_level, _aspect_ratio * _zoom_level,
                -_zoom_level, _zoom_level);
        }

        auto set_zoom_level(float zoom) -> void
        {
            _zoom_level = zoom;
        }

        auto get_zoom_level() const -> float
        {
            return _zoom_level;
        }

        auto get_camera() -> orthographic_camera*
        {
            return &_camera;
        }

    private:
        auto handle(window_event& event) -> void
        {
            switch (event.event_type)
            {
                case window_event_type::resize:
                    _on_window_resize_event(reinterpret_cast<window_resize_event&>(event));
                    break;

                default: break;
            }
        }

        auto _on_window_resize_event(window_resize_event& event) -> void
        {
            // todo: refactor this.
            on_resize({ event.size.x, event.size.y });
        }

        auto handle(mouse_event& event) -> void
        {
            switch (event.event_type)
            {
                case mouse_event_type::scroll_event:
                    _on_mouse_scroll_event(reinterpret_cast<mouse_scroll_event&>(event));
                    break;

                default: break;
            }
        }

        auto _on_mouse_scroll_event(mouse_scroll_event& event) -> void
        {
            _zoom_level -= event.yoffset.to_unwrapped<float>() * _zoom_speed;
            _zoom_level = math::max_of(_zoom_level, 0.25f);

            _camera.set_projection(-_aspect_ratio * _zoom_level, _aspect_ratio * _zoom_level,
                -_zoom_level, _zoom_level);
        }

    private:
        float _aspect_ratio;
        float _zoom_level;
        float _zoom_speed;
        float _move_speed;
        float _rotation_speed;
        vec3 _position;
        float _rotation;
        window* _window;
        keyboard* _keyboard;
        mouse* _mouse;
        orthographic_camera _camera;
    };
}
