import atom.core;
import atom.logging;

#include "atom/engine/window/window_manager.h"
#include "engine/glfw/glfw_window.h"

#include "GLFW/glfw3.h"

using namespace atom;
using namespace atom::logging;

namespace atom::engine
{
    auto window_manager::initialize() -> void
    {
        _logger = logger_manager::create_logger({ .name = "window_manager" }).get_value();

        glfwSetErrorCallback(
            [](int error_code, const char* description) -> void {
                ATOM_PANIC("glfw error: error_code: {}, description: {}", error_code, description);
            });

        _logger->log_info("initializing glfw...");
        int success = glfwInit();

        if (success == GLFW_FALSE)
        {
            _logger->log_info("glfw initialization failed.");
            ATOM_PANIC("glfw initialization failed.");
        }

        _logger->log_info("initialized glfw successfully.");
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

        window* window = new glfw_window(props);
        _windows.emplace_back(window);

        _logger->log_info("created window.");
        window_create_event event(window);
        _event_source.dispatch(event);

        return window;
    }

    auto window_manager::destroy_window(window* window) -> void
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

    auto window_manager::destroy_all_windows() -> void
    {
        for (window* window : _windows)
        {
            // `window_destroy_event` will be dispatched from the window itself.

            delete window;
        }
    }

    dynamic_array<window*> window_manager::_windows;
    event_source<window_event> window_manager::_event_source;
    logging::logger* window_manager::_logger;
}
