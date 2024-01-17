module;
#include "GLFW/glfw3.h"

export module atom.engine:window_manager;
import :window;
import :window.glfw;
import atom.core;
import atom.logging;

using namespace Atom;
using namespace Atom::Logging;

namespace Atom::Engine
{
    class LinuxWindow: public GlfwWindow
    {
    public:
        LinuxWindow(const WindowProps& props)
            : GlfwWindow(props)
        {}
    };

    class WindowsWindow: public GlfwWindow
    {
    public:
        WindowsWindow(const WindowProps& props)
            : GlfwWindow(props)
        {}
    };

    export class WindowProps
    {
    public:
        String windowName;
        WindowCoords windowSize;
    };

    export class WindowManger
    {
    public:
        static auto CreateWindow(WindowProps props) -> Window*
        {
            if (s_windowCount == 0)
            {
                int success = glfwInit();
                Contracts::Asserts(success, "GLFW initialization failed.");

                glfwSetErrorCallback([](_i32 error_code, const char* description) {
                    // TODO: Fix this compilation error.
                    // LOG_FATAL("GLFW Error: ", description);
                });
            }

            s_windowCount++;
            return new _CreateWindow(props);
        }

        static auto CloseWindow(Window* window)
        {
            Contracts::Expects(window != nullptr, "Cannot close NULL window.");

            delete window;
        }

    private:
        static auto _CreateWindow(WindowProps props)
        {
            if constexpr (BuildConfig::GetPlatform() == BuildConfig::Platform::Posix)
                return LinuxWindow(props);
            else if constexpr (BuildConfig::GetPlatform() == BuildConfig::Platform::Windows)
                return WindowsWindow(props);
            else
                static_assert(false, "Atom::Engine::Window is only supported for Linux and Windows "
                                     "platform for now.");
        }

    protected:
        static usize s_windowCount;
    };

    static usize WindowManager::s_windowCount = 0;
}
