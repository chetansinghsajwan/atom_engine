module;
#include "GLFW/glfw3.h"

export module atom.engine:window_manager;
import :window;
import :glfw_window;
import atom.core;
import atom.logging;

using namespace atom;
using namespace atom::logging;

namespace atom::engine
{
    class linux_window: public glfw_window
    {
    public:
        linux_window(const window_props& props)
            : glfw_window(props)
        {}
    };

    class windows_window: public glfw_window
    {
    public:
        windows_window(const window_props& props)
            : glfw_window(props)
        {}
    };

    export class window_manager
    {
    public:
        static auto create_window(window_props props) -> window*
        {
            if (s_window_count == 0)
            {
                int success = glfwInit();
                contracts::asserts(success, "glfw initialization failed.");

                glfwSetErrorCallback([](_i32 error_code, const char* description) {
                    // todo: fix this compilation error.
                    // log_fatal("glfw error: ", description);
                });
            }

            s_window_count++;
            return _create_window(props);
        }

        static auto close_window(window* window)
        {
            contracts::expects(window != nullptr, "cannot close null window.");

            delete window;
        }

    private:
        static auto _create_window(window_props props) -> window*
        {
            if constexpr (build_config::get_platform() == build_config::platform::posix)
                return new linux_window(props);
            else if constexpr (build_config::get_platform() == build_config::platform::windows)
                return new windows_window(props);
            else
            {
                // static_assert(sizeof(bool) != 1, "atom::engine::window is only supported for linux and windows "
                //                      "platform for now.");
            }
        }

    protected:
        static usize s_window_count;
    };

    usize window_manager::s_window_count = 0;
}
