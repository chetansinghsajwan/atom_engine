module;
#include "GLFW/glfw3.h"

module atom.engine:windows.window_manager.impl;
import :windows.window_manager;

import atom.core;
import atom.logging;
import :glfw;
import :windows.window_events;

namespace atom::engine
{
    auto window_manager::initialize() -> void
    {
        _logger = logging::logger_manager::create_logger({ .name = "window_manager" }).get_value();

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

        glfwTerminate();

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
}
