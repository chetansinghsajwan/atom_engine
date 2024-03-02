#pragma once
#include "atom.core.h"
#include "atom.logging.h"
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

        static auto get_windows() -> array_view<window*>;

    private:
        static inline dynamic_array<window*> _s_windows;
        static inline event_source<const window_event&> _s_event_source;
        static inline logging::logger* _logger;

    public:
        static inline event_source_view<const window_event&> event = _s_event_source;
    };
}
