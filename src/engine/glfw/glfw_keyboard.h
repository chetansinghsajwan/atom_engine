#pragma once
#include "atom/engine/inputs/keyboard.h"
#include "engine/glfw/glfw_window.h"
#include "engine/glfw/glfw_keyboard_key_conversions.h"

#include "GLFW/glfw3.h"
#include "backends/imgui_impl_glfw.h"

namespace atom::engine
{
    class glfw_keyboard: public keyboard
    {
    public:
        glfw_keyboard(glfw_window* window, input_device_id id, string name)
            : keyboard(id, move(name))
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
