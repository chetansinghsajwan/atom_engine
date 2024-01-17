#pragma once
#include "Atom/Engine/Windows.h"

namespace Atom::Engine
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

    public:
        virtual auto Run() -> void;

        virtual auto OnWindowEvent(const WindowEvent& event) -> void;

    protected:
        Window* _window;
    };

    extern Application* CreateApplication();
}
