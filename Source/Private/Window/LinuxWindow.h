#pragma once
#include "Window/GlfwWindow.h"

namespace Atom::Engine
{
    class LinuxWindow: public GlfwWindow
    {
    public:
        LinuxWindow(const WindowProps& props)
            : GlfwWindow(props)
        {}
    };
}
