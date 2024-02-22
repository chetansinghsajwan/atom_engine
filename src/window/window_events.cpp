export module atom.engine:window_events;
import atom.core;

namespace atom::engine
{
    export extern "C++" class window;

    export struct window_coords
    {
        i32 x;
        i32 y;
    };

    export class window_props
    {
    public:
        string window_name;
        window_coords window_size;
    };

    export inline auto operator-(const window_coords& lhs, const window_coords& rhs)
        -> window_coords
    {
        return { lhs.x - rhs.x, lhs.y - rhs.y };
    }

    export enum class window_event_type
    {
        create,
        close,
        resize,
        reposition,
    };

    export class window_event
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

    export class window_create_event: public window_event
    {
    public:
        window_create_event(window* win)
            : window_event(win, window_event_type::create)
        {}
    };

    export class window_close_event: public window_event
    {
    public:
        window_close_event(window* win)
            : window_event(win, window_event_type::close)
        {}
    };

    export class window_resize_event: public window_event
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

    export class window_reposition_event: public window_event
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
}
