#include "glfw_window.h"

#include "glad/glad.h"

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
            coords.x = coords.x.clamp(i32::min(), i32::max());
            coords.y = coords.y.clamp(i32::min(), i32::max());

            return { coords.x, coords.y };
        };

        static constexpr auto from_glfw(glfw_window_coords coords) -> window_coords
        {
            coords.x = coords.x.clamp(i32::min(), i32::max());
            coords.y = coords.y.clamp(i32::min(), i32::max());

            return { coords.x, coords.y };
        };
    };

    glfw_window::glfw_window(const window_props& props)
        : window(props.window_name)
        , _user_data()
    {
        glfw_window_coords glfw_window_size =
            glfw_window_coords_converter::to_glfw(props.window_size);

        _glfw_window = glfwCreateWindow(glfw_window_size.x.to_unwrapped<int>(),
            glfw_window_size.y.to_unwrapped<int>(), props.window_name.get_data(), nullptr, nullptr);

        glfwMakeContextCurrent(_glfw_window);

        _user_data.window = this;
        glfwSetWindowUserPointer(_glfw_window, &_user_data);

        int glad_load_status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        contracts::asserts(glad_load_status != 0, "glad inititliazation failed.");

        glfwSetWindowPosCallback(_glfw_window, [](GLFWwindow* native_window, int xpos, int ypos) {
            glfw_window_user_data* user_data =
                (glfw_window_user_data*)glfwGetWindowUserPointer(native_window);
            glfw_window* window = user_data->window;

            window_coords old_pos = window->_window_pos;
            window_coords new_pos = glfw_window_coords_converter::from_glfw({ xpos, ypos });
            window->_window_pos = new_pos;

            window_reposition_event event(window, new_pos, new_pos - old_pos);
            window->_event_source.dispatch(event);
        });

        glfwSetWindowSizeCallback(
            _glfw_window, [](GLFWwindow* native_window, int width, int height) {
                glfw_window_user_data* user_data =
                    (glfw_window_user_data*)glfwGetWindowUserPointer(native_window);
                glfw_window* window = user_data->window;

                window_coords old_size = window->_window_size;
                window_coords new_size = glfw_window_coords_converter::from_glfw({ width, height });
                window->_window_size = new_size;

                window_resize_event event(window, new_size, new_size - old_size);
                window->_event_source.dispatch(event);
            });

        glfwSetWindowCloseCallback(_glfw_window, [](GLFWwindow* native_window) {
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

    glfw_window::~glfw_window()
    {
        glfwDestroyWindow(_glfw_window);
    }

    auto glfw_window::update() -> void
    {
        glfwPollEvents();
        glfwSwapBuffers(_glfw_window);
    }

    auto glfw_window::set_pos(window_coords pos) -> void
    {
        glfw_window_coords glfw_pos = glfw_window_coords_converter::to_glfw(pos);

        glfwSetWindowPos(_glfw_window, glfw_pos.x.to_unwrapped(), glfw_pos.y.to_unwrapped());
        _window_pos = glfw_window_coords_converter::from_glfw(glfw_pos);
    }

    auto glfw_window::get_pos() const -> window_coords
    {
        return _window_pos;
    }

    auto glfw_window::update_pos() -> window_coords
    {
        int x, y;
        glfwGetWindowPos(_glfw_window, &x, &y);

        return glfw_window_coords_converter::from_glfw(glfw_window_coords{ x, y });
    }

    auto glfw_window::set_size(window_coords size) -> void
    {
        glfw_window_coords glfw_size = glfw_window_coords_converter::to_glfw(size);

        glfwSetWindowSize(_glfw_window, glfw_size.x.to_unwrapped(), glfw_size.y.to_unwrapped());
        _window_size = glfw_window_coords_converter::from_glfw(glfw_size);
    }

    auto glfw_window::get_size() const -> window_coords
    {
        return _window_size;
    }

    auto glfw_window::update_size() -> window_coords
    {
        int x;
        int y;
        glfwGetWindowSize(_glfw_window, &x, &y);

        _window_size = glfw_window_coords_converter::from_glfw(glfw_window_coords{ x, y });
        return _window_size;
    }
}
