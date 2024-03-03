#pragma once
#include "atom.core.h"
#include "atom/engine/events.h"
#include "atom/engine/inputs/mouse.h"
#include "atom/engine/inputs/mouse_buttons.h"
#include "atom/engine/inputs/mouse_events.h"
#include "engine/glfw/glfw_window.h"
#include "engine/glfw/glfw_mouse_button_conversions.h"

#include "GLFW/glfw3.h"

namespace atom::engine
{
    class glfw_mouse: public mouse
    {
    public:
        glfw_mouse(glfw_window* window, input_device_id id, string name);

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
