#pragma once
// #include "atom.core.h"
#include "atom/engine/events.h"

namespace atom::engine
{
    class window;

    struct window_coords
    {
        i32 x;
        i32 y;
    };

    struct window_props
    {
        string window_name;
        window_coords window_size;
    };

    inline auto operator-(const window_coords& lhs, const window_coords& rhs) -> window_coords
    {
        return { lhs.x - rhs.x, lhs.y - rhs.y };
    }

    enum struct window_event_type
    {
        create,
        destroy,
        focus,
        resize,
        reposition,
    };

    struct window_event: event_base
    {
        window_event(window_event_type event_type, window* win)
            : event_type(event_type)
            , win(win)
        {}

        window_event(window_event_type event_type)
            : win(nullptr)
            , event_type(event_type)
        {}

        const window* win;
        const window_event_type event_type;
    };

    struct window_create_event: window_event
    {
        window_create_event(window* win)
            : window_event(window_event_type::create, win)
        {}
    };

    struct window_destroy_event: window_event
    {
        window_destroy_event(window* win)
            : window_event(window_event_type::destroy, win)
        {}
    };

    struct window_focus_event: window_event
    {
        window_focus_event(window* win, bool is_focused)
            : window_event(window_event_type::focus, win)
            , is_focused(is_focused)
        {}

        bool is_focused;
    };

    struct window_resize_event: window_event
    {
        window_resize_event(window* win, window_coords size, window_coords delta)
            : size(size)
            , delta(delta)
            , window_event(window_event_type::resize, win)
        {}

        window_coords size;
        window_coords delta;
    };

    struct window_reposition_event: window_event
    {
        window_reposition_event(window* win, window_coords position, window_coords delta)
            : position(position)
            , delta(delta)
            , window_event(window_event_type::reposition, win)
        {}

        window_coords position;
        window_coords delta;
    };

    struct window_event_listener: event_listener<window_event>
    {};
}
