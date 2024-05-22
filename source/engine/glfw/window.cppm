module;
#include "GLFW/glfw3.h"
#include "glad/glad.h"

export module atom.engine:glfw.window;

import atom.core;
import :windows;
import :events;
import :opengl;
import :glfw.window_user_data;

namespace atom::engine
{
    class glfw_window_coords
    {
    public:
        i32 x;
        i32 y;
    };

    class glfw_window_coords_converter
    {
    public:
        static constexpr auto to_glfw(window_coords coords) -> glfw_window_coords
        {
            coords.x = math::clamp(coords.x, math::min<i32>(), math::max<i32>());
            coords.y = math::clamp(coords.y, math::min<i32>(), math::max<i32>());

            return { coords.x, coords.y };
        };

        static constexpr auto from_glfw(glfw_window_coords coords) -> window_coords
        {
            coords.x = math::clamp(coords.x, math::min<i32>(), math::max<i32>());
            coords.y = math::clamp(coords.y, math::min<i32>(), math::max<i32>());

            return { coords.x, coords.y };
        };
    };
    
    class glfw_window: public window
    {
    public:
        glfw_window(const window_props& props)
            : window(props.window_name)
            , _user_data()
            , _graphics_context(nullptr)
        {
            glfw_window_coords glfw_window_size =
                glfw_window_coords_converter::to_glfw(props.window_size);

            _glfw_window = glfwCreateWindow(glfw_window_size.x, glfw_window_size.y,
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

                    window_coords old_pos = window->_window_pos;
                    window_coords new_pos = glfw_window_coords_converter::from_glfw({ xpos, ypos });
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

                    window_coords old_size = window->_window_size;
                    window_coords new_size =
                        glfw_window_coords_converter::from_glfw({ width, height });
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

        virtual auto set_pos(window_coords pos) -> void override
        {
            glfw_window_coords glfw_pos = glfw_window_coords_converter::to_glfw(pos);

            glfwSetWindowPos(_glfw_window, glfw_pos.x, glfw_pos.y);
            _window_pos = glfw_window_coords_converter::from_glfw(glfw_pos);
        }

        virtual auto get_pos() const -> window_coords override
        {
            return _window_pos;
        }

        virtual auto update_pos() -> window_coords
        {
            int x;
            int y;
            glfwGetWindowPos(_glfw_window, &x, &y);

            return glfw_window_coords_converter::from_glfw(glfw_window_coords{ x, y });
        }

        virtual auto set_size(window_coords size) -> void override
        {
            glfw_window_coords glfw_size = glfw_window_coords_converter::to_glfw(size);

            glfwSetWindowSize(_glfw_window, glfw_size.x, glfw_size.y);
            _window_size = glfw_window_coords_converter::from_glfw(glfw_size);
        }

        virtual auto get_size() const -> window_coords override
        {
            return _window_size;
        }

        virtual auto update_size() -> window_coords
        {
            int x;
            int y;
            glfwGetWindowSize(_glfw_window, &x, &y);

            _window_size = glfw_window_coords_converter::from_glfw(glfw_window_coords{ x, y });
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
        window_coords _window_pos;
        window_coords _window_size;
        bool _window_vsync;
        event_source<window_event> _event_source;
        glfw_window_user_data _user_data;
        opengl_context* _graphics_context;
    };
}
