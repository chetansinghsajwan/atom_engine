#pragma once
#include "atom.core.h"
#include "atom/engine/inputs/mouse.h"
#include "engine/glfw/glfw_window.h"
#include "engine/glfw/glfw_mouse_button_conversions.h"

#include "GLFW/glfw3.h"

namespace atom::engine
{
    class glfw_mouse: public mouse
    {
    public:
        glfw_mouse(glfw_window* window, input_device_id id, string name)
            : mouse(id, move(name))
            , _window(window)
            , _delta_scroll()
        {
            glfwSetScrollCallback(
                _window->get_native_glfw(), [](GLFWwindow* window, double x, double y) {
                    // todo: review glfw window user pointer.
                    glfw_mouse* this_mouse =
                        reinterpret_cast<glfw_mouse*>(glfwGetWindowUserPointer(window));

                    this_mouse->_delta_scroll = vec2(x, y);
                });
        }

    protected:
        virtual auto _get_button_state(mouse_button_code button) const
            -> mouse_button_state override final
        {
            int state = glfwGetMouseButton(
                _window->get_native_glfw(), convert_mouse_button_code_atom_to_glfw(button));
            return convert_mouse_button_state_glfw_to_atom(state);
        }

        virtual auto _get_delta_move() const -> vec2 override final
        {
            double xpos, ypos;
            glfwGetCursorPos(_window->get_native_glfw(), &xpos, &ypos);
            return vec2(xpos, ypos);
        }

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

        virtual auto _get_delta_scroll() const -> vec2 override final
        {
            return _delta_scroll;
        }

    private:
        glfw_window* _window;
        vec2 _delta_scroll;
    };
}
