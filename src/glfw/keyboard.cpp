module;
#include "GLFW/glfw3.h"

export module atom.engine:glfw_keyboard;
import :glfw_window;
import :glfw_keyboard_key_code_conversions;
import :input_device;
import :keyboard;
import :keyboard_key_codes;
import :keyboard_events;
import atom.core;

namespace atom::engine
{
    class glfw_keyboard: public keyboard
    {
    public:
        glfw_keyboard(glfw_window* window, input_device_id id, string name)
            : keyboard(id, name)
            , _window(window)
        {}

    protected:
        virtual auto _get_key_state(keyboard_key_code key) const
            -> keyboard_key_state override final
        {
            int state =
                glfwGetKey(_window->get_native_glfw(), convert_keyboard_key_code_atom_to_glfw(key));
            return convert_keyboard_key_state_glfw_to_atom(state);
        }

    public:
        glfw_window* _window;
    };
}
