#include "glfw_mouse.h"
#include "engine/glfw/glfw_window_user_data.h"

namespace atom::engine
{
    glfw_mouse::glfw_mouse(glfw_window* window, input_device_id id, string name)
        : mouse(id, move(name))
        , _window(window)
        , _prev_mouse_button_callback(nullptr)
        , _prev_scroll_callback(nullptr)
        , _prev_cursor_pos_callback(nullptr)
        , _chain_prev_callbacks(false)
    {
        glfw_window_user_data* user_data =
            (glfw_window_user_data*)glfwGetWindowUserPointer(window->get_native_glfw());

        user_data->mouse = this;

        _prev_cursor_pos_callback = glfwSetCursorPosCallback(
            _window->get_native_glfw(), [](GLFWwindow* window, double xpos, double ypos) -> void {
                glfw_window_user_data* user_data =
                    reinterpret_cast<glfw_window_user_data*>(glfwGetWindowUserPointer(window));
                glfw_mouse* mouse = user_data->mouse;

                if (mouse->_chain_prev_callbacks and mouse->_prev_cursor_pos_callback != nullptr)
                {
                    mouse->_prev_cursor_pos_callback(window, xpos, ypos);
                }

                mouse->_last_pos_x = mouse->_pos_x;
                mouse->_last_pos_y = mouse->_pos_y;
                mouse->_pos_x = xpos;
                mouse->_pos_y = ypos;
                f64 delta_pos_x = mouse->_pos_x - mouse->_last_pos_x;
                f64 delta_pos_y = mouse->_pos_y - mouse->_last_pos_y;

                mouse_move_event event(mouse, xpos, ypos, delta_pos_x, delta_pos_y);
                mouse->_event_source.dispatch(event);
            });

        _prev_mouse_button_callback = glfwSetMouseButtonCallback(_window->get_native_glfw(),
            [](GLFWwindow* window, int button, int action, int mods) -> void {
                glfw_window_user_data* user_data =
                    reinterpret_cast<glfw_window_user_data*>(glfwGetWindowUserPointer(window));
                glfw_mouse* mouse = user_data->mouse;

                if (mouse->_chain_prev_callbacks and mouse->_prev_mouse_button_callback != nullptr)
                {
                    mouse->_prev_mouse_button_callback(window, button, action, mods);
                }

                mouse_button_code button_code = convert_mouse_button_code_glfw_to_atom(button);
                mouse_button_state button_state = convert_mouse_button_state_glfw_to_atom(action);

                mouse->_button_states[(usize)button_code] = button_state;

                mouse_button_event event(mouse, button_code, button_state);
                mouse->_event_source.dispatch(event);
            });

        _prev_scroll_callback = glfwSetScrollCallback(_window->get_native_glfw(),
            [](GLFWwindow* window, double xoffset, double yoffset) -> void {
                glfw_window_user_data* user_data =
                    reinterpret_cast<glfw_window_user_data*>(glfwGetWindowUserPointer(window));
                glfw_mouse* mouse = user_data->mouse;

                if (mouse->_chain_prev_callbacks and mouse->_prev_scroll_callback != nullptr)
                {
                    mouse->_prev_scroll_callback(window, xoffset, yoffset);
                }

                mouse->_last_scroll_pos_x = mouse->_scroll_pos_x;
                mouse->_last_scroll_pos_y = mouse->_scroll_pos_y;
                mouse->_scroll_pos_x = xoffset;
                mouse->_scroll_pos_y = yoffset;
                f64 delta_scroll_pos_x = mouse->_scroll_pos_x - mouse->_last_scroll_pos_x;
                f64 delta_scroll_pos_y = mouse->_scroll_pos_y - mouse->_last_scroll_pos_y;

                mouse_scroll_event event(
                    mouse, xoffset, yoffset, delta_scroll_pos_x, delta_scroll_pos_y);
                mouse->_event_source.dispatch(event);
            });
    }
}
