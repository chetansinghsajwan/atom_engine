module;
#include "GLFW/glfw3.h"
#include "glad/glad.h"

export module atom_engine:glfw.window;

import atom_core;
import :math;
import :windows;
import :events;
import :opengl;
import :glfw.window_user_data;

namespace atom::engine
{
    class glfw_window: public window
    {
    public:
        glfw_window(const window_props& props)
            : window(props.window_name)
            , _user_data()
            , _graphics_context(nullptr)
        {
            _glfw_window = glfwCreateWindow(props.window_size.x, props.window_size.y,
                props.window_name.get_data(), nullptr, nullptr);

            _graphics_context = new opengl_context(_glfw_window);
            _graphics_context->initialize();

            _user_data.window = this;
            glfwSetWindowUserPointer(_glfw_window, &_user_data);

            int glad_load_status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            contract_asserts(glad_load_status != 0, "glad inititliazation failed.");

            glfwSetWindowPosCallback(_glfw_window,
                [](GLFWwindow* native_window, int xpos, int ypos)
                {
                    glfw_window_user_data* user_data =
                        (glfw_window_user_data*)glfwGetWindowUserPointer(native_window);
                    glfw_window* window = user_data->window;

                    i32vec2 old_pos = window->_window_pos;
                    i32vec2 new_pos = { xpos, ypos };
                    window->_window_pos = new_pos;

                    window_reposition_event event(window, new_pos, new_pos - old_pos);
                    window->_event_source.dispatch(event);
                });

            glfwSetWindowSizeCallback(_glfw_window,
                [](GLFWwindow* native_window, int width, int height)
                {
                    glfw_window_user_data* user_data =
                        (glfw_window_user_data*)glfwGetWindowUserPointer(native_window);
                    glfw_window* window = user_data->window;

                    i32vec2 old_size = window->_window_size;
                    i32vec2 new_size = { width, height };
                    window->_window_size = new_size;

                    window_resize_event event(window, new_size, new_size - old_size);
                    window->_event_source.dispatch(event);
                });

            glfwSetWindowCloseCallback(_glfw_window,
                [](GLFWwindow* native_window)
                {
                    glfw_window_user_data* user_data =
                        (glfw_window_user_data*)glfwGetWindowUserPointer(native_window);
                    glfw_window* window = user_data->window;

                    window_destroy_event event(window);
                    window->_event_source.dispatch(event);
                });

            update_pos();
            update_size();
            set_vsync(true);
        }

        ~glfw_window()
        {
            glfwDestroyWindow(_glfw_window);
        }

    public:
        virtual auto update() -> void override
        {
            glfwPollEvents();
            _graphics_context->swap_buffers();
        }

        virtual auto set_pos(i32vec2 pos) -> void override
        {
            glfwSetWindowPos(_glfw_window, pos.x, pos.y);
            _window_pos = pos;
        }

        virtual auto get_pos() const -> i32vec2 override
        {
            return _window_pos;
        }

        virtual auto update_pos() -> i32vec2
        {
            int x;
            int y;
            glfwGetWindowPos(_glfw_window, &x, &y);

            return i32vec2{ x, y };
        }

        virtual auto set_size(i32vec2 size) -> void override
        {
            glfwSetWindowSize(_glfw_window, size.x, size.y);
            _window_size = size;
        }

        virtual auto get_size() const -> i32vec2 override
        {
            return _window_size;
        }

        virtual auto update_size() -> i32vec2
        {
            int x;
            int y;
            glfwGetWindowSize(_glfw_window, &x, &y);

            _window_size = i32vec2{ x, y };
            return _window_size;
        }

        virtual auto is_minimized() const -> bool override
        {
            return _window_size.x == 0 || _window_size.y == 0;
        }

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
        i32vec2 _window_pos;
        i32vec2 _window_size;
        bool _window_vsync;
        event_source<window_event> _event_source;
        glfw_window_user_data _user_data;
        opengl_context* _graphics_context;
    };
}
