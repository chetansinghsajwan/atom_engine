#include "Atom/CoreAll.h"
#include "Atom/Logging.h"

#if defined(ATOM_PLATFORM_POSIX)
#    include "Window/LinuxWindow.h"
using PlatformSelectedWindow = Atom::Engine::LinuxWindow;

#elif defined(ATOM_PLATFORM_WINDOWS)
#    include "Window/WindowsWindow.h"
using PlatformSelectedWindow = Atom::Engine::WindowsWindow;

#else
#    error "Atom::Engine::Window is only supported for Linux and Windows platform for now."

#endif

using namespace Atom::Logging;

namespace Atom::Engine
{
    auto WindowManger::CreateWindow(WindowProps props) -> Window*
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
        return new PlatformSelectedWindow(props);
    }

    auto WindowManger::CloseWindow(Window* window) -> void
    {
        Contracts::Expects(window != nullptr, "Cannot close NULL window.");

        delete window;
    }

    usize WindowManger::s_windowCount = 0;
}
