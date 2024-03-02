#pragma once
#include "atom.core.h"
#include "atom/engine/window/window_events.h"

namespace atom::engine
{
    class window
    {
    public:
        window(string name, event_source_view<const window_event&> event)
            : _name(move(name))
            , event{ event }
        {}

        virtual ~window() = default;

    public:
        auto get_name() const -> string_view
        {
            return _name;
        }

        virtual auto update() -> void = 0;

        virtual auto get_size() const -> window_coords = 0;
        virtual auto set_size(window_coords size) -> void = 0;

        virtual auto get_pos() const -> window_coords = 0;
        virtual auto set_pos(window_coords pos) -> void = 0;

        virtual auto get_native() const -> void* = 0;

    public:
        event_source_view<const window_event&> event;

    private:
        string _name;
    };
}
