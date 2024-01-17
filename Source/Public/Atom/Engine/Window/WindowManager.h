#pragma once
#include "Atom/CoreAll.h"
#include "Atom/Engine/Window/Window.h"

namespace Atom::Engine
{
    class WindowProps
    {
    public:
        String windowName;
        WindowCoords windowSize;
    };

    class WindowManger
    {
    public:
        static auto CreateWindow(WindowProps props) -> Window*;

        static auto CloseWindow(Window* window) -> void;

    protected:
        static usize s_windowCount;
    };
}
