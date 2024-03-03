#pragma once
#include "atom.core.h"
#include "atom/engine/inputs/input_device.h"
#include "atom/engine/inputs/mouse_buttons.h"
#include "atom/engine/inputs/mouse_events.h"
#include "atom/engine/math.h"

namespace atom::engine
{
    class mouse: public input_device
    {
    public:
        mouse(input_device_id id, string name)
            : input_device(id, move(name))
        {}

        virtual ~mouse() {}

    public:
        auto get_button_state(mouse_button_code button) const -> mouse_button_state
        {
            return _button_states[(usize::unwrapped_type)button];
        }

        auto is_button_up(mouse_button_code button) const -> bool
        {
            return get_button_state(button) == mouse_button_state::up;
        }

        auto is_button_pressed(mouse_button_code button) const -> bool
        {
            return get_button_state(button) == mouse_button_state::pressed;
        }

        auto is_button_down(mouse_button_code button) const -> bool
        {
            return get_button_state(button) == mouse_button_state::down;
        }

        auto is_button_released(mouse_button_code button) const -> bool
        {
            return get_button_state(button) == mouse_button_state::released;
        }

        auto get_pos() const -> vec2
        {
            return vec2(_pos_x, _pos_y);
        }

        auto get_last_pos() const -> vec2
        {
            return vec2(_last_pos_x, _last_pos_y);
        }

        auto get_delta_pos() const -> vec2
        {
            return vec2(_pos_x - _last_pos_x, _pos_y - _last_pos_y);
        }

        auto is_raw_move_supported() const -> bool
        {
            return _is_raw_move_supported();
        }

        auto is_raw_move_enabled() const -> bool
        {
            return _is_raw_move_enabled();
        }

        auto set_raw_move(bool enable) -> void
        {
            return _set_raw_move(enable);
        }

        auto get_scroll_pos() const -> vec2
        {
            return vec2(_scroll_pos_x, _scroll_pos_y);
        }

        auto get_last_scroll_pos() const -> vec2
        {
            return vec2(_last_scroll_pos_x, _last_scroll_pos_y);
        }

        auto get_delta_scroll_pos() const -> vec2
        {
            return vec2(_scroll_pos_x - _last_scroll_pos_x, _scroll_pos_y - _last_scroll_pos_y);
        }

    protected:
        virtual auto _is_raw_move_enabled() const -> bool = 0;
        virtual auto _is_raw_move_supported() const -> bool = 0;
        virtual auto _set_raw_move(bool enable) -> void = 0;

    protected:
        mouse_button_state _button_states[(usize::unwrapped_type)mouse_button_code::MAX + 1];
        f64 _pos_x;
        f64 _pos_y;
        f64 _last_pos_x;
        f64 _last_pos_y;
        f64 _scroll_pos_x;
        f64 _scroll_pos_y;
        f64 _last_scroll_pos_x;
        f64 _last_scroll_pos_y;
    };
}
