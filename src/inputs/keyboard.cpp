export module atom.engine:keyboard;
import :keyboard_key_codes;
import :keyboard_events;
import atom.core;

namespace atom::engine
{
    export class keyboard
    {
    public:
        keyboard() = default;

        virtual ~keyboard() = default;

    public:
        auto get_key_state(keyboard_key_code key) const -> keyboard_key_state
        {
            return _get_key_state(key);
        }

        auto is_key_up(keyboard_key_code key) const -> bool
        {
            return get_key_state(key) == keyboard_key_state::up;
        }

        auto is_key_pressed(keyboard_key_code key) const -> bool
        {
            return get_key_state(key) == keyboard_key_state::pressed;
        }

        auto is_key_down(keyboard_key_code key) const -> bool
        {
            return get_key_state(key) == keyboard_key_state::down;
        }

        auto is_key_released(keyboard_key_code key) const -> bool
        {
            return get_key_state(key) == keyboard_key_state::released;
        }

    protected:
        virtual auto _get_key_state(keyboard_key_code) const -> keyboard_key_state = 0;
    };
}
