#pragma once
#include "engine/rendering/orthographic_camera.h"
#include "orthographic_camera.h"
#include "atom/engine/inputs/keyboard.h"
#include "atom/engine/inputs/mouse.h"
#include "atom/engine/window/window.h"
#include "atom/engine/time.h"
#include "atom/engine/math.h"

namespace atom::engine
{
    class orthographic_camera_controller
    {
    public:
        orthographic_camera_controller(float aspect_ratio);

    public:
        auto on_update(time_stemp delta_time) -> void;

        auto set_keyboard(class keyboard* keyboard) -> void;

        auto get_camera() -> orthographic_camera*
        {
            return &_camera;
        }

    private:
        auto _on_window_event(const window_event& event) -> void;
        auto _on_window_resize_event(const window_resize_event& event) -> void;

        auto _on_mouse_event(const mouse_event& event) -> void;
        auto _on_mouse_scroll_event(const mouse_scroll_event& event) -> void;

    private:
        float _aspect_ratio;
        float _zoom_level;
        float _move_speed;
        float _rotation_speed;
        vec3 _position;
        float _rotation;
        keyboard* _keyboard;
        orthographic_camera _camera;
    };
}
