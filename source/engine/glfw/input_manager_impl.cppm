module;
#include "GLFW/glfw3.h"

export module atom.engine:glfw.input_manager_impl;

import atom.core;
import :inputs;
import :windows;
import :glfw.mouse;
import :glfw.keyboard;
import :glfw.window;

namespace atom::engine
{
    class glfw_input_manager_impl
        : public input_manager_impl
        , public window_event_listener
    {
    public:
        glfw_input_manager_impl()
            : input_manager_impl()
        {
            for (class window* window : window_manager::get_windows())
            {
                _create_devices_for_window(reinterpret_cast<glfw_window*>(window));
            }

            window_manager::subscribe_event(this);
        }

        ~glfw_input_manager_impl()
        {
            destroy_all_devices();
        }

    public:
        auto destroy_all_devices() -> void
        {
            for (input_device* device : _devices)
            {
                delete device;
            }

            _devices.remove_all();
        }

    private:
        virtual auto on_event(window_event& event) -> void override
        {
            _create_devices_for_window(
                reinterpret_cast<glfw_window*>(const_cast<window*>(event.window)));
        }

        auto _create_devices_for_window(glfw_window* window) -> void
        {
            input_device_id keyboard_id = input_manager_impl::_create_new_id();
            string keyboard_name =
                string::format("glfw_keyboard for window '{0}'", window->get_name());
            glfw_keyboard* keyboard = new glfw_keyboard(window, keyboard_id, move(keyboard_name));
            input_manager_impl::_add_new_device(keyboard);

            input_device_id mouse_id = input_manager_impl::_create_new_id();
            string mouse_name = string::format("glfw_mouse for window '{0}'", window->get_name());
            glfw_mouse* mouse = new glfw_mouse(window, mouse_id, move(mouse_name));
            input_manager_impl::_add_new_device(mouse);
        }
    };
}
