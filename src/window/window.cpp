export module atom.engine:window;
import :window_events;
import atom.core;

namespace atom::engine
{
    export extern "C++" class window
    {
    public:
        window(event_source_view<const window_event&> event)
            : event{ event }
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
        event_source_view<const window_event&> event;
    };
}
