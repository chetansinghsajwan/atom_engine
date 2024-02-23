export module atom.engine:mouse;
import :input_device;
import :mouse_button_codes;
import :mouse_events;
import :math;

namespace atom::engine
{
    export class mouse: public input_device
    {
    public:
        mouse(input_device_id id, string name)
            : input_device(id, name)
        {}

        virtual ~mouse() = default;

    public:
        auto get_button_state(mouse_button_code button) const -> mouse_button_state
        {
            return _get_button_state(button);
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

        auto get_delta_move() const -> vec2
        {
            return _get_delta_move();
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

        auto get_delta_scroll() const -> vec2
        {
            return _get_delta_scroll();
        }

    protected:
        virtual auto _get_button_state(mouse_button_code button) const -> mouse_button_state = 0;
        virtual auto _get_delta_move() const -> vec2 = 0;
        virtual auto _is_raw_move_enabled() const -> bool = 0;
        virtual auto _is_raw_move_supported() const -> bool = 0;
        virtual auto _set_raw_move(bool enable) -> void = 0;
        virtual auto _get_delta_scroll() const -> vec2 = 0;
    };
}
