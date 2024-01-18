export module atom.engine:window;
import atom.core;

namespace atom::engine
{
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

    export inline auto operator-(const window_coords& lhs, const window_coords& rhs) -> window_coords
    {
        return { lhs.x - rhs.x, lhs.y - rhs.y };
    }

    export enum class ewindow_event_type
    {
        resize,
        reposition,
        close,
    };

    export class window_event
    {
    public:
        window_event(ewindow_event_type event_type)
            : event_type(event_type)
        {}

    public:
        const ewindow_event_type event_type;
    };

    export class window_resize_event: public window_event
    {
    public:
        window_resize_event(window_coords size, window_coords delta)
            : size(size)
            , delta(delta)
            , window_event(ewindow_event_type::resize)
        {}

    public:
        window_coords size;
        window_coords delta;
    };

    export class window_reposition_event: public window_event
    {
    public:
        window_reposition_event(window_coords position, window_coords delta)
            : position(position)
            , delta(delta)
            , window_event(ewindow_event_type::reposition)
        {}

    public:
        window_coords position;
        window_coords delta;
    };

    export class window_close_event: public window_event
    {
    public:
        window_close_event()
            : window_event(ewindow_event_type::close)
        {}
    };

    export class window
    {
    public:
        window(ievent<const window_event&>& event)
            : on_event{ event }
        {}

    public:
        virtual ~window() = default;

        virtual auto update() -> void = 0;

        virtual auto get_size() const -> window_coords = 0;
        virtual auto set_size(window_coords size) -> void = 0;

        virtual auto get_pos() const -> window_coords = 0;
        virtual auto set_pos(window_coords pos) -> void = 0;

        virtual auto get_native() const -> void* = 0;

    public:
        ievent<const window_event&>& on_event;
    };
}
