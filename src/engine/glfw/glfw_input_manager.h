#pragma once
#include "atom.core.h"
#include "atom/engine/inputs/input_manager_impl.h"
#include "atom/engine/window/window.h"
#include "atom/engine/window/window_manager.h"
#include "engine/glfw/glfw_keyboard.h"
#include "engine/glfw/glfw_mouse.h"
#include "engine/glfw/glfw_window.h"

#include "GLFW/glfw3.h"

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
            for (window* win : window_manager::get_windows())
            {
                _create_devices_for_window(reinterpret_cast<glfw_window*>(win));
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
        virtual auto handle(window_event& event) -> void override
        {
            _create_devices_for_window(
                reinterpret_cast<glfw_window*>(const_cast<window*>(event.win)));
        }

        auto _create_devices_for_window(glfw_window* win) -> void
        {
            input_device_id keyboard_id = input_manager_impl::_create_new_id();
            string keyboard_name =
                string::format("glfw_keyboard for window '{0}'", win->get_name());
            glfw_keyboard* keyboard = new glfw_keyboard(win, keyboard_id, move(keyboard_name));
            input_manager_impl::_add_new_device(keyboard);

            input_device_id mouse_id = input_manager_impl::_create_new_id();
            string mouse_name = string::format("glfw_mouse for window '{0}'", win->get_name());
            glfw_mouse* mouse = new glfw_mouse(win, mouse_id, move(mouse_name));
            input_manager_impl::_add_new_device(mouse);
        }
    };
}
