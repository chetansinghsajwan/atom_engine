#pragma once
#include "engine/rendering/orthographic_camera.h"
#include "orthographic_camera.h"
#include "atom/engine/window/window.h"
#include "atom/engine/inputs/keyboard.h"
#include "atom/engine/inputs/mouse.h"
#include "atom/engine/time.h"
#include "atom/engine/math.h"

namespace atom::engine
{
    class orthographic_camera_controller
        : public window_event_listener
        , mouse_event_listener
    {
    public:
        orthographic_camera_controller(float aspect_ratio);

    public:
        auto on_update(time_step delta_time) -> void;

        auto set_window(class window* window) -> void;
        auto set_keyboard(class keyboard* keyboard) -> void;
        auto set_mouse(class mouse* mouse) -> void;

        auto on_resize(vec2 size) -> void;

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
        auto handle(window_event& event) -> void;
        auto _on_window_resize_event(window_resize_event& event) -> void;

        auto handle(mouse_event& event) -> void;
        auto _on_mouse_scroll_event(mouse_scroll_event& event) -> void;

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
