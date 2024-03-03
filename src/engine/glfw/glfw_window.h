#pragma once
#include "atom/engine/window/window.h"
#include "engine/glfw/glfw_window_user_data.h"

#include "GLFW/glfw3.h"

namespace atom::engine
{
    class glfw_window: public window
    {
    public:
        glfw_window(const window_props& props);

        ~glfw_window();

    public:
        virtual auto update() -> void override;

        virtual auto set_pos(window_coords pos) -> void override;

        virtual auto get_pos() const -> window_coords override;

        virtual auto update_pos() -> window_coords;

        virtual auto set_size(window_coords size) -> void override;

        virtual auto get_size() const -> window_coords override;

        virtual auto update_size() -> window_coords;

        virtual auto get_native() const -> void* override final
        {
            return _glfw_window;
        }

        auto get_native_glfw() const -> GLFWwindow*
        {
            return _glfw_window;
        }

        auto set_vsync(bool enable) -> void
        {
            glfwSwapInterval(enable ? 1 : 0);
            _window_vsync = enable;
        }

        auto get_vsync() const -> bool
        {
            return _window_vsync;
        }

        virtual auto subscribe_event(window_event_listener* listener) -> void override
        {
            _event_source.subscribe(listener);
        }

        virtual auto unsubscribe_event(window_event_listener* listener) -> void override
        {
            _event_source.unsubscribe(listener);
        }

    private:
        GLFWwindow* _glfw_window;
        window_coords _window_pos;
        window_coords _window_size;
        bool _window_vsync;
        event_source<window_event> _event_source;
        glfw_window_user_data _user_data;
    };
}
