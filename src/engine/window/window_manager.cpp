#include "atom/engine/window/window_manager.h"
#include "engine/glfw/glfw_window.h"

#include "GLFW/glfw3.h"

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

    auto window_manager::initialize() -> void
    {
        _logger = logger_manager::create_logger({ .name = "window_manager" }).get_at<0>();

        _logger->log_info("initializing glfw...");
        int success = glfwInit();

        if (success == 0)
        {
            _logger->log_info("glfw initialization failed.");
            panic("glfw initialization failed.");
        }

        _logger->log_info("initialized glfw successfully.");

        glfwSetErrorCallback([](_i32 error_code, const char* description) -> void {
            panic("glfw error: error_code: {}, description: {}", error_code, description);
        });
    }

    auto window_manager::finalize() -> void
    {
        _logger->log_info("destroying all windows...");
        destroy_all_windows();
        _logger->log_info("destroyed all windows.");
    }

    auto window_manager::create_window(window_props props) -> window*
    {
        _logger->log_info("creating window '{}'.", props.window_name);

        window* window = _create_window(props);
        _windows.emplace_back(window);

        _logger->log_info("created window.");
        window_create_event event(window);
        _event_source.dispatch(event);

        return window;
    }

    auto window_manager::destroy_window(window* window) -> void
    {
        contracts::expects(window != nullptr, "cannot close null window.");

        _logger->log_info("destroying window '{}'.", window->get_name());
        if (_windows.remove_one_find(window))
        {
            _logger->log_info("window not found in window_manager's entries.");
            return;
        }

        _logger->log_info("destroyed window.");
        window_close_event event(window);
        _event_source.dispatch(event);
        _destroy_window(window);
    }

    auto window_manager::destroy_all_windows() -> void
    {
        for (window* window : _windows)
        {
            // `window_close_event` will be dispatched from the window itself.

            _destroy_window(window);
        }
    }
}
