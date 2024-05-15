export module atom.engine:inputs.mouse_events;

import atom.core;
import :events;
import :inputs.mouse_buttons;

namespace atom::engine
{
    export class mouse;

    export enum struct mouse_event_type
    {
        create_event,
        destroy_event,
        button_event,
        move_event,
        scroll_event,
    };

    export struct mouse_event: event_base
    {
        mouse_event(mouse_event_type event_type, mouse* device)
            : event_type(event_type)
            , device(device)
        {}

        mouse_event_type event_type;
        mouse* device;
    };

    export struct mouse_button_event: mouse_event
    {
        mouse_button_event(mouse* device, mouse_button_code button, mouse_button_state state)
            : mouse_event(mouse_event_type::button_event, device)
            , button(button)
            , state(state)
        {}

        mouse_button_code button;
        mouse_button_state state;
    };

    export struct mouse_move_event: mouse_event
    {
        mouse_move_event(mouse* device, f64 xpos, f64 ypos, f64 xdelta, f64 ydelta)
            : mouse_event(mouse_event_type::move_event, device)
            , xpos(xpos)
            , ypos(ypos)
            , xdelta(xdelta)
            , ydelta(ydelta)
        {}

        f64 xpos;
        f64 ypos;
        f64 xdelta;
        f64 ydelta;
    };

    export struct mouse_scroll_event: mouse_event
    {
        mouse_scroll_event(mouse* device, f64 xoffset, f64 yoffset, f64 xdelta, f64 ydelta)
            : mouse_event(mouse_event_type::scroll_event, device)
            , xoffset(xoffset)
            , yoffset(yoffset)
            , xdelta(xdelta)
            , ydelta(ydelta)
        {}

        f64 xoffset;
        f64 yoffset;
        f64 xdelta;
        f64 ydelta;
    };

    export struct mouse_event_listener: event_listener<mouse_event>
    {};
}
