export module atom.engine:windows.window_events;

import atom.core;
import :events;

namespace atom::engine
{
    class window;

    export struct window_coords
    {
        i32 x;
        i32 y;
    };

    export struct window_props
    {
        string window_name;
        window_coords window_size;
    };

    export inline auto operator-(
        const window_coords& lhs, const window_coords& rhs) -> window_coords
    {
        return { lhs.x - rhs.x, lhs.y - rhs.y };
    }

    export enum struct window_event_type
    {
        create,
        destroy,
        focus,
        resize,
        reposition,
    };

    export struct window_event: event_base
    {
        window_event(window_event_type event_type, class window* window)
            : event_type(event_type)
            , window(window)
        {}

        window_event(window_event_type event_type)
            : window(nullptr)
            , event_type(event_type)
        {}

        const class window* window;
        const window_event_type event_type;
    };

    export struct window_create_event: window_event
    {
        window_create_event(class window* window)
            : window_event(window_event_type::create, window)
        {}
    };

    export struct window_destroy_event: window_event
    {
        window_destroy_event(class window* window)
            : window_event(window_event_type::destroy, window)
        {}
    };

    export struct window_focus_event: window_event
    {
        window_focus_event(class window* window, bool is_focused)
            : window_event(window_event_type::focus, window)
            , is_focused(is_focused)
        {}

        bool is_focused;
    };

    export struct window_resize_event: window_event
    {
        window_resize_event(class window* window, window_coords size, window_coords delta)
            : size(size)
            , delta(delta)
            , window_event(window_event_type::resize, window)
        {}

        window_coords size;
        window_coords delta;
    };

    export struct window_reposition_event: window_event
    {
        window_reposition_event(class window* window, window_coords position, window_coords delta)
            : position(position)
            , delta(delta)
            , window_event(window_event_type::reposition, window)
        {}

        window_coords position;
        window_coords delta;
    };

    export struct window_event_listener: event_listener<window_event>
    {};
}
