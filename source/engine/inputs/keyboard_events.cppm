export module atom.engine:inputs.keyboard_events;

import atom.core;
import :events;
import :inputs.keyboard_keys;

namespace atom::engine
{
    export class keyboard;
    export using unicode_code_point = u32;

    export enum struct keyboard_event_type
    {
        create_event,
        destroy_event,
        key_event,
        char_event,
    };

    export struct keyboard_event: event_base
    {
        keyboard_event(keyboard_event_type event_type, keyboard* device)
            : event_type(event_type)
            , device(device)
        {}

        keyboard_event_type event_type;
        keyboard* device;
    };

    export struct keyboard_create_event: keyboard_event
    {
        keyboard_create_event(keyboard* device)
            : keyboard_event(keyboard_event_type::create_event, device)
        {}
    };

    export struct keyboard_destroy_event: keyboard_event
    {
        keyboard_destroy_event(keyboard* device)
            : keyboard_event(keyboard_event_type::destroy_event, device)
        {}
    };

    export struct keyboard_key_event: keyboard_event
    {
        keyboard_key_event(keyboard* device, keyboard_key_code key, keyboard_key_state state)
            : keyboard_event(keyboard_event_type::key_event, device)
            , key(key)
            , state(state)
        {}

        keyboard_key_code key;
        keyboard_key_state state;
    };

    export struct keyboard_char_event: keyboard_event
    {
        keyboard_char_event(keyboard* device, unicode_code_point ch)
            : keyboard_event(keyboard_event_type::char_event, device)
            , ch(ch)
        {}

        unicode_code_point ch;
    };

    export struct keyboard_event_listener: event_listener<keyboard_event>
    {};
}
