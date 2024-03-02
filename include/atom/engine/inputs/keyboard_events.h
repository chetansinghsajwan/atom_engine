#pragma once
#include "atom.core.h"
#include "atom/engine/inputs/keyboard_events.h"
#include "atom/engine/inputs/keyboard_keys.h"

namespace atom::engine
{
    class keyboard;
    using unicode_code_point = u32;

    class keyboard_event
    {
    public:
        keyboard_event(keyboard* device)
            : device(device)
        {}

    public:
        keyboard* device;
    };

    class keyboard_key_event: public keyboard_event
    {
    public:
        keyboard_key_event(keyboard* device, keyboard_key_code key, keyboard_key_state state)
            : keyboard_event(device)
            , key(key)
            , state(state)
        {}

    public:
        keyboard_key_code key;
        keyboard_key_state state;
    };

    class keyboard_char_event: public keyboard_event
    {
    public:
        keyboard_char_event(keyboard* device, unicode_code_point ch)
            : keyboard_event(device)
            , ch(ch)
        {}

    public:
        unicode_code_point ch;
    };
}
