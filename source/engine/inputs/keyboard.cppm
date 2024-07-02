export module atom.engine:inputs.keyboard;

import atom_core;
import :inputs.input_device;
import :inputs.keyboard_keys;
import :inputs.keyboard_events;

namespace atom::engine
{
    export class keyboard: public input_device
    {
    public:
        keyboard(input_device_id id, string name)
            : input_device(id, input_device_type::keyboard, move(name))
            , _key_states()
        {}

        virtual ~keyboard() {}

    public:
        auto get_key_state(keyboard_key_code key) const -> keyboard_key_state
        {
            return _key_states[(usize)key];
        }

        auto is_key_up(keyboard_key_code key) const -> bool
        {
            keyboard_key_state state = get_key_state(key);
            return state == keyboard_key_state::up || state == keyboard_key_state::released;
        }

        auto is_key_pressed(keyboard_key_code key) const -> bool
        {
            return get_key_state(key) == keyboard_key_state::pressed;
        }

        auto is_key_down(keyboard_key_code key) const -> bool
        {
            keyboard_key_state state = get_key_state(key);
            return state == keyboard_key_state::down || state == keyboard_key_state::pressed;
        }

        auto is_key_released(keyboard_key_code key) const -> bool
        {
            return get_key_state(key) == keyboard_key_state::released;
        }

        virtual auto subscribe_event(keyboard_event_listener* listener) -> void = 0;

        virtual auto unsubscribe_event(keyboard_event_listener* listener) -> void = 0;

    protected:
        keyboard_key_state _key_states[(usize)keyboard_key_code::MAX + 1];
    };
}
