module;
#include "GLFW/glfw3.h"

export module atom.engine:glfw_input_manager_impl;
import :input_manager_impl;
import :input_device;
import :window_manager;
import :window_events;
import :glfw_mouse;
import :glfw_keyboard;
import :glfw_window;
import atom.core;

namespace atom::engine
{
    export class glfw_input_manager_impl: public input_manager_impl
    {
    public:
        glfw_input_manager_impl()
            : input_manager_impl()
        {
            for (window* win : window_manager::get_windows())
            {
                _create_devices_for_window(reinterpret_cast<glfw_window*>(win));
            }

            window_manager::event += [this](const window_event& event) {
                if (event.event_type == window_event_type::create)
                {
                    this->_on_window_create(reinterpret_cast<const window_create_event&>(event));
                }
            };
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
        auto _on_window_create(const window_create_event& event) -> void
        {
            _create_devices_for_window(reinterpret_cast<glfw_window*>(const_cast<window*>(event.win)));
        }

        auto _create_devices_for_window(glfw_window* win) -> void
        {
            input_device_id keyboard_id = input_manager_impl::_create_new_id();
            string keyboard_name =
                string::format("glfw_keyboard for window '{0}'", win->get_name());
            glfw_keyboard* keyboard_device =
                new glfw_keyboard(win, keyboard_id, move(keyboard_name));
            input_manager_impl::_add_new_device(keyboard_device);

            input_device_id mouse_id = input_manager_impl::_create_new_id();
            string mouse_name = string::format("glfw_mouse for window '{0}'", win->get_name());
            glfw_mouse* mouse_device = new glfw_mouse(win, mouse_id, move(mouse_name));
            input_manager_impl::_add_new_device(mouse_device);
        }
    };
}
