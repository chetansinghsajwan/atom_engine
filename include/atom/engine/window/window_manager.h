#pragma once
// #include "atom.core.h"
// #include "atom.logging.h"
#include "atom/engine/window/window.h"
#include "atom/engine/window/window_events.h"

namespace atom::engine
{
    class window_manager
    {
    public:
        static auto initialize() -> void;

        static auto finalize() -> void;

        static auto create_window(window_props props) -> window*;

        static auto destroy_window(window* window) -> void;

        static auto destroy_all_windows() -> void;

        static auto get_windows() -> array_slice<window*>
        {
            return _windows;
        }

        static auto subscribe_event(window_event_listener* listener) -> void
        {
            _event_source.subscribe(listener);
        }

        static auto unsubscribe_event(window_event_listener* listener) -> void
        {
            _event_source.unsubscribe(listener);
        }

    private:
        static dynamic_array<window*> _windows;
        static event_source<window_event> _event_source;
        static logging::logger* _logger;
    };
}
