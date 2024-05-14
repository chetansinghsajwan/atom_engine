import atom.core;
import atom.logging;

#include "glfw_keyboard.h"
#include "engine/glfw/glfw_window_user_data.h"

namespace atom::engine
{
    glfw_keyboard::glfw_keyboard(glfw_window* window, input_device_id id, string name)
        : keyboard(id, move(name))
        , _window(window)
        , _event_source()
        , _prev_key_callback(nullptr)
        , _prev_char_callback(nullptr)
        , _chain_prev_callbacks(true)
    {
        ATOM_DEBUG_EXPECTS(window != nullptr);

        glfw_window_user_data* user_data =
            (glfw_window_user_data*)glfwGetWindowUserPointer(window->get_native_glfw());

        user_data->keyboard = this;

        _prev_key_callback = glfwSetKeyCallback(window->get_native_glfw(),
            [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void {
                glfw_window_user_data* user_data =
                    (glfw_window_user_data*)glfwGetWindowUserPointer(window);
                glfw_keyboard* keyboard = user_data->keyboard;

                if (keyboard->_chain_prev_callbacks and keyboard->_prev_key_callback != nullptr)
                {
                    keyboard->_prev_key_callback(window, key, scancode, action, mods);
                }

                keyboard_key_code key_code = convert_keyboard_key_code_glfw_to_atom(key);
                keyboard_key_state key_state = convert_keyboard_key_state_glfw_to_atom(action);

                keyboard->_key_states[(usize)key_code] = key_state;

                keyboard_key_event event(keyboard, key_code, key_state);
                keyboard->_event_source.dispatch(event);
            });

        _prev_char_callback = glfwSetCharCallback(
            window->get_native_glfw(), [](GLFWwindow* window, unsigned int codepoint) -> void {
                glfw_window_user_data* user_data =
                    (glfw_window_user_data*)glfwGetWindowUserPointer(window);
                glfw_keyboard* keyboard = user_data->keyboard;

                if (keyboard->_chain_prev_callbacks and keyboard->_prev_char_callback != nullptr)
                {
                    keyboard->_prev_char_callback(window, codepoint);
                }

                keyboard_char_event event(keyboard, codepoint);
                keyboard->_event_source.dispatch(event);
            });
    }
}
