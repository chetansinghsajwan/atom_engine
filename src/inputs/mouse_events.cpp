export module atom.engine:mouse_events;
import :mouse_button_codes;
import atom.core;

namespace atom::engine
{
    export class mouse;

    export class mouse_event
    {
    public:
        mouse_event(mouse* device)
            : device(device)
        {}

    public:
        mouse* device;
    };

    export class mouse_button_event: public mouse_event
    {
    public:
        mouse_button_event(mouse* device, mouse_button_code button, mouse_button_state state)
            : mouse_event(device)
            , button(button)
            , state(state)
        {}

    public:
        const mouse_button_code button;
        const mouse_button_state state;
    };

    export class mouse_move_event: public mouse_event
    {
    public:
        mouse_move_event(mouse* device, f64 delta_x, f64 delta_y)
            : mouse_event(device)
            , delta_x(delta_x)
            , delta_y(delta_y)
        {}

    public:
        const f64 delta_x;
        const f64 delta_y;
    };

    export class mouse_scroll_event: public mouse_event
    {
    public:
        mouse_scroll_event(mouse* device, f64 delta_x, f64 delta_y)
            : mouse_event(device)
            , delta_x(delta_x)
            , delta_y(delta_y)
        {}

    public:
        const f64 delta_x;
        const f64 delta_y;
    };
}
