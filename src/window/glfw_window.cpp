module;
#include "GLFW/glfw3.h"
#include "glad/glad.h"

export module atom.engine:glfw_window;
import atom.core;
import atom.logging;
import :window;

using namespace atom;
using namespace atom::logging;

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

    class glfw_window: public window
    {
    public:
        glfw_window(const window_props& props)
            : window(_window_event_source)
        {
            glfw_window_coords glfw_window_size =
                glfw_window_coords_converter::to_glfw(props.window_size);

            _glfw_window = glfwCreateWindow(glfw_window_size.x.to_unwrapped<int>(),
                glfw_window_size.y.to_unwrapped<int>(), props.window_name.to_std_char_ptr(),
                nullptr, nullptr);

            glfwMakeContextCurrent(_glfw_window);
            glfwSetWindowUserPointer(_glfw_window, this);

            int glad_load_status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            contracts::asserts(glad_load_status != 0, "glad inititliazation failed.");

            glfwSetWindowPosCallback(
                _glfw_window, [](GLFWwindow* native_window, _i32 xpos, _i32 ypos) {
                    glfw_window& window = *reinterpret_cast<class glfw_window*>(
                        glfwGetWindowUserPointer(native_window));

                    window_coords old_pos = window._window_pos;
                    window_coords new_pos = glfw_window_coords_converter::from_glfw({ xpos, ypos });
                    window._window_pos = new_pos;

                    window._window_event_source.dispatch(
                        window_reposition_event(new_pos, new_pos - old_pos));
                });

            glfwSetWindowSizeCallback(_glfw_window, [](GLFWwindow* native_window, _i32 width,
                                                        _i32 height) {
                glfw_window& window =
                    *reinterpret_cast<class glfw_window*>(glfwGetWindowUserPointer(native_window));

                window_coords old_size = window._window_size;
                window_coords new_size = glfw_window_coords_converter::from_glfw({ width, height });
                window._window_size = new_size;

                window._window_event_source.dispatch(
                    window_resize_event(new_size, new_size - old_size));
            });

            glfwSetWindowCloseCallback(_glfw_window, [](GLFWwindow* native_window) {
                glfw_window& window =
                    *reinterpret_cast<class glfw_window*>(glfwGetWindowUserPointer(native_window));

                window._window_event_source.dispatch(window_close_event());
            });

            update_pos();
            update_size();
            set_vsync(true);
        }

        ~glfw_window()
        {
            glfwDestroyWindow(_glfw_window);
        }

        virtual auto update() -> void override
        {
            glfwPollEvents();
            glfwSwapBuffers(_glfw_window);
        }

        virtual auto set_pos(window_coords pos) -> void override
        {
            glfw_window_coords glfw_pos = glfw_window_coords_converter::to_glfw(pos);

            glfwSetWindowPos(_glfw_window, glfw_pos.x.to_unwrapped(), glfw_pos.y.to_unwrapped());
            _window_pos = glfw_window_coords_converter::from_glfw(glfw_pos);
        }

        virtual auto get_pos() const -> window_coords override
        {
            return _window_pos;
        }

        virtual auto update_pos() -> window_coords
        {
            int x, y;
            glfwGetWindowPos(_glfw_window, &x, &y);

            return glfw_window_coords_converter::from_glfw(glfw_window_coords{ x, y });
        }

        virtual auto set_size(window_coords size) -> void override
        {
            glfw_window_coords glfw_size = glfw_window_coords_converter::to_glfw(size);

            glfwSetWindowSize(_glfw_window, glfw_size.x.to_unwrapped(), glfw_size.y.to_unwrapped());
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

        virtual auto get_native() const -> void* override final
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

    protected:
        GLFWwindow* _glfw_window;
        window_coords _window_pos;
        window_coords _window_size;
        bool _window_vsync;

        event_source<const window_event&> _window_event_source;
    };
}
