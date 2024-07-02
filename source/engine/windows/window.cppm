export module atom.engine:windows.window;

import atom_core;
import :math;
import :windows.window_events;

namespace atom::engine
{
    class window
    {
    public:
        window(string name)
            : _name(move(name))
        {}

        virtual ~window() = default;

    public:
        auto get_name() const -> string_view
        {
            return _name;
        }

        virtual auto update() -> void = 0;

        virtual auto is_minimized() const -> bool = 0;
        virtual auto get_size() const -> i32vec2 = 0;
        virtual auto set_size(i32vec2 size) -> void = 0;

        virtual auto get_pos() const -> i32vec2 = 0;
        virtual auto set_pos(i32vec2 pos) -> void = 0;

        virtual auto get_native() const -> void* = 0;

        virtual auto subscribe_event(window_event_listener* listener) -> void = 0;
        virtual auto unsubscribe_event(window_event_listener* listener) -> void = 0;

    private:
        string _name;
    };
}
