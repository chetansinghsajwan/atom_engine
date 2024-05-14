#pragma once
// #include "atom.core.h"
#include "atom/engine/events.h"
#include "atom/engine/inputs/keyboard_keys.h"

namespace atom::engine
{
    class keyboard;
    using unicode_code_point = u32;

    enum struct keyboard_event_type
    {
        create_event,
        destroy_event,
        key_event,
        char_event,
    };

    struct keyboard_event: event_base
    {
        keyboard_event(keyboard_event_type event_type, keyboard* device)
            : event_type(event_type)
            , device(device)
        {}

        keyboard_event_type event_type;
        keyboard* device;
    };

    struct keyboard_create_event: keyboard_event
    {
        keyboard_create_event(keyboard* device)
            : keyboard_event(keyboard_event_type::create_event, device)
        {}
    };

    struct keyboard_destroy_event: keyboard_event
    {
        keyboard_destroy_event(keyboard* device)
            : keyboard_event(keyboard_event_type::destroy_event, device)
        {}
    };

    struct keyboard_key_event: keyboard_event
    {
        keyboard_key_event(keyboard* device, keyboard_key_code key, keyboard_key_state state)
            : keyboard_event(keyboard_event_type::key_event, device)
            , key(key)
            , state(state)
        {}

        keyboard_key_code key;
        keyboard_key_state state;
    };

    struct keyboard_char_event: keyboard_event
    {
        keyboard_char_event(keyboard* device, unicode_code_point ch)
            : keyboard_event(keyboard_event_type::char_event, device)
            , ch(ch)
        {}

        unicode_code_point ch;
    };

    struct keyboard_event_listener: event_listener<keyboard_event>
    {};
}
