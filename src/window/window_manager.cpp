module;
#include "GLFW/glfw3.h"

export module atom.engine:window_manager;
import :window;
import :window_events;
import :glfw_window;
import atom.core;
import atom.logging;

using namespace atom;
using namespace atom::logging;

namespace atom::engine
{
    class linux_window: public glfw_window
    {
    public:
        linux_window(const window_props& props)
            : glfw_window(props)
        {}
    };

    class windows_window: public glfw_window
    {
    public:
        windows_window(const window_props& props)
            : glfw_window(props)
        {}
    };

    export class window_manager
    {
    public:
        static auto init() -> void
        {
            int success = glfwInit();
            contracts::asserts(success, "glfw initialization failed.");

            glfwSetErrorCallback([](_i32 error_code, const char* description) {
                // todo: fix this compilation error.
                // log_fatal("glfw error: ", description);
            });
        }

        static auto shutdown() -> void
        {
            destroy_all_windows();
        }

        static auto create_window(window_props props) -> window*
        {
            window* window = _create_window(props);
            _s_windows.emplace_back(window);
            _s_event_source.dispatch(window_create_event(window));

            return window;
        }

        // should we rename this to close_window?
        static auto destroy_window(window* window) -> void
        {
            contracts::expects(window != nullptr, "cannot close null window.");
            if (_s_windows.remove_find(window) == usize::max())
            {
                // todo: log here: window not found in window_manager's entries.
                return;
            }

            _s_event_source.dispatch(window_close_event(window));
            _destroy_window(window);
        }

        static auto destroy_all_windows() -> void
        {
            for (window* window : _s_windows)
            {
                // wind ow_close_event will be dispatched from the window itself.

                _destroy_window(window);
            }
        }

    private:
        static auto _create_window(window_props props) -> window*
        {
            if constexpr (build_config::get_platform() == build_config::platform::posix)
                return new linux_window(props);
            else if constexpr (build_config::get_platform() == build_config::platform::windows)
                return new windows_window(props);
            else
            {
                // static_assert(sizeof(bool) != 1, "atom::engine::window is only supported for linux and windows "
                //                      "platform for now.");
            }
        }

        static auto _destroy_window(window* window) -> void
        {
            delete window;
        }

    public:
        static event_source_view<const window_event&> event;

    private:
        static inline dynamic_array<window*> _s_windows;
        static inline event_source<const window_event&> _s_event_source;
    };
}
