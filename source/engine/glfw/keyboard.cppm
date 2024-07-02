module;
#include "GLFW/glfw3.h"

export module atom.engine:glfw.keyboard;

import atom_core;
import :inputs;
import :events;
import :glfw.window;
import :glfw.keyboard_conversions;

namespace atom::engine
{
    class glfw_keyboard: public keyboard
    {
    public:
        glfw_keyboard(glfw_window* window, input_device_id id, string name)
            : keyboard(id, move(name))
            , _window(window)
            , _event_source()
            , _prev_key_callback(nullptr)
            , _prev_char_callback(nullptr)
            , _chain_prev_callbacks(true)
        {
            contract_debug_expects(window != nullptr);

            glfw_window_user_data* user_data =
                (glfw_window_user_data*)glfwGetWindowUserPointer(window->get_native_glfw());

            user_data->keyboard = this;

            _prev_key_callback = glfwSetKeyCallback(window->get_native_glfw(),
                [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void
                {
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

            _prev_char_callback = glfwSetCharCallback(window->get_native_glfw(),
                [](GLFWwindow* window, unsigned int codepoint) -> void
                {
                    glfw_window_user_data* user_data =
                        (glfw_window_user_data*)glfwGetWindowUserPointer(window);
                    glfw_keyboard* keyboard = user_data->keyboard;

                    if (keyboard->_chain_prev_callbacks
                        and keyboard->_prev_char_callback != nullptr)
                    {
                        keyboard->_prev_char_callback(window, codepoint);
                    }

                    keyboard_char_event event(keyboard, codepoint);
                    keyboard->_event_source.dispatch(event);
                });
        }

    public:
        virtual auto subscribe_event(keyboard_event_listener* listener) -> void override
        {
            _event_source.subscribe(listener);
        }

        virtual auto unsubscribe_event(keyboard_event_listener* listener) -> void override
        {
            _event_source.unsubscribe(listener);
        }

    public:
        glfw_window* _window;
        GLFWkeyfun _prev_key_callback;
        GLFWcharfun _prev_char_callback;
        bool _chain_prev_callbacks;
        event_source<keyboard_event> _event_source;
    };
}
