#pragma once
#include "atom.core.h"
#include "atom/engine/events.h"

namespace atom::engine
{
    class window;

    struct window_coords
    {
        i32 x;
        i32 y;
    };

    class window_props
    {
    public:
        string window_name;
        window_coords window_size;
    };

    inline auto operator-(const window_coords& lhs, const window_coords& rhs)
        -> window_coords
    {
        return { lhs.x - rhs.x, lhs.y - rhs.y };
    }

    enum class window_event_type
    {
        create,
        close,
        resize,
        reposition,
    };

    class window_event: public event_base
    {
    public:
        window_event(window* win, window_event_type event_type)
            : win(win)
            , event_type(event_type)
        {}

        window_event(window_event_type event_type)
            : win(nullptr)
            , event_type(event_type)
        {}

    public:
        const window* win;
        const window_event_type event_type;
    };

    class window_create_event: public window_event
    {
    public:
        window_create_event(window* win)
            : window_event(win, window_event_type::create)
        {}
    };

    class window_close_event: public window_event
    {
    public:
        window_close_event(window* win)
            : window_event(win, window_event_type::close)
        {}
    };

    class window_resize_event: public window_event
    {
    public:
        window_resize_event(window* win, window_coords size, window_coords delta)
            : size(size)
            , delta(delta)
            , window_event(win, window_event_type::resize)
        {}

    public:
        window_coords size;
        window_coords delta;
    };

    class window_reposition_event: public window_event
    {
    public:
        window_reposition_event(window* win, window_coords position, window_coords delta)
            : position(position)
            , delta(delta)
            , window_event(win, window_event_type::reposition)
        {}

    public:
        window_coords position;
        window_coords delta;
    };

    class window_event_listener: public event_listener<window_event>
    {};

}
