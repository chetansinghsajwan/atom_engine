export module atom.engine:windows.window_manager;

import atom.core;
import atom.logging;
import :events;
import :windows.window;
import :windows.window_events;

namespace atom::engine
{
    export class window_manager
    {
    public:
        static auto initialize() -> void;

        static auto finalize() -> void;

        static auto create_window(window_props props) -> window*;

        static auto destroy_window(window* window) -> void
        {
            ATOM_EXPECTS(window != nullptr, "cannot close null window.");

            _logger->log_info("destroying window '{}'.", window->get_name());
            if (not _windows.remove_one_find(window))
            {
                _logger->log_info("window not found in window_manager's entries.");
                return;
            }

            _logger->log_info("destroyed window.");
            window_destroy_event event(window);
            _event_source.dispatch(event);
            delete window;
        }

        static auto destroy_all_windows() -> void
        {
            for (window* window : _windows)
            {
                // `window_destroy_event` will be dispatched from the window itself.

                delete window;
            }
        }

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
        static inline dynamic_array<window*> _windows;
        static inline event_source<window_event> _event_source;
        static inline logging::logger* _logger;
    };
}
