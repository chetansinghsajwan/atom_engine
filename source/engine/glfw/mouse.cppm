module;
#include "GLFW/glfw3.h"

export module atom.engine:glfw.mouse;

import atom.core;
import :inputs;
import :events;
import :glfw.mouse_conversions;
import :glfw.window;

namespace atom::engine
{
    class glfw_mouse: public mouse
    {
    public:
        glfw_mouse(glfw_window* window, input_device_id id, string name)
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

            _prev_cursor_pos_callback = glfwSetCursorPosCallback(_window->get_native_glfw(),
                [](GLFWwindow* window, double xpos, double ypos) -> void
                {
                    glfw_window_user_data* user_data =
                        reinterpret_cast<glfw_window_user_data*>(glfwGetWindowUserPointer(window));
                    glfw_mouse* mouse = user_data->mouse;

                    if (mouse->_chain_prev_callbacks
                        and mouse->_prev_cursor_pos_callback != nullptr)
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
                [](GLFWwindow* window, int button, int action, int mods) -> void
                {
                    glfw_window_user_data* user_data =
                        reinterpret_cast<glfw_window_user_data*>(glfwGetWindowUserPointer(window));
                    glfw_mouse* mouse = user_data->mouse;

                    if (mouse->_chain_prev_callbacks
                        and mouse->_prev_mouse_button_callback != nullptr)
                    {
                        mouse->_prev_mouse_button_callback(window, button, action, mods);
                    }

                    mouse_button_code button_code = convert_mouse_button_code_glfw_to_atom(button);
                    mouse_button_state button_state =
                        convert_mouse_button_state_glfw_to_atom(action);

                    mouse->_button_states[(usize)button_code] = button_state;

                    mouse_button_event event(mouse, button_code, button_state);
                    mouse->_event_source.dispatch(event);
                });

            _prev_scroll_callback = glfwSetScrollCallback(_window->get_native_glfw(),
                [](GLFWwindow* window, double xoffset, double yoffset) -> void
                {
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

    public:
        virtual auto subscribe_event(mouse_event_listener* listener) -> void override
        {
            _event_source.subscribe(listener);
        }

        virtual auto unsubscribe_event(mouse_event_listener* listener) -> void override
        {
            _event_source.unsubscribe(listener);
        }

    protected:
        virtual auto _is_raw_move_supported() const -> bool override final
        {
            return glfwRawMouseMotionSupported();
        }

        virtual auto _is_raw_move_enabled() const -> bool override final
        {
            return glfwGetInputMode(_window->get_native_glfw(), GLFW_RAW_MOUSE_MOTION) == GLFW_TRUE;
        }

        virtual auto _set_raw_move(bool enable) -> void override final
        {
            glfwSetInputMode(
                _window->get_native_glfw(), GLFW_RAW_MOUSE_MOTION, enable ? GLFW_TRUE : GLFW_FALSE);
        }

    private:
        event_source<mouse_event> _event_source;
        glfw_window* _window;
        GLFWmousebuttonfun _prev_mouse_button_callback;
        GLFWscrollfun _prev_scroll_callback;
        GLFWcursorposfun _prev_cursor_pos_callback;
        bool _chain_prev_callbacks;
    };
}
