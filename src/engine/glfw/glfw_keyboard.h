#pragma once
#include "atom/engine/inputs/keyboard.h"
#include "atom/engine/events.h"
#include "atom/engine/inputs/keyboard_events.h"
#include "engine/glfw/glfw_window.h"
#include "engine/glfw/glfw_keyboard_key_conversions.h"

#include "GLFW/glfw3.h"

namespace atom::engine
{
    class glfw_keyboard: public keyboard
    {
    public:
        glfw_keyboard(glfw_window* window, input_device_id id, string name);

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
