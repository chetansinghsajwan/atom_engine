export module atom.engine:keyboard_events;
import :keyboard_key_codes;
import atom.core;

namespace atom::engine
{
    export class keyboard;
    using unicode_code_point = u32;

    export class keyboard_event
    {
    public:
        keyboard_event(keyboard* device)
            : device(device)
        {}

    public:
        keyboard* device;
    };

    export class keyboard_key_event: public keyboard_event
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

    export class keyboard_char_event: public keyboard_event
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
