#include "Atom/Engine/Application.h"

namespace Atom::Engine
{
    Application::Application()
    {
        WindowProps windowProps{
            .windowName = "Sandbox", .windowSize = {1920, 1080}
        };

        _window = WindowManger::CreateWindow(windowProps);
        debug_asserts(_window != nullptr);

        _window->OnEvent += [this](const SWindowEvent& event) { this->OnWindowEvent(event); };
    }

    Application::~Application()
    {
        if (_window != nullptr)
        {
            WindowManger::CloseWindow(_window);
        }
    }

    auto Application::Run() -> void
    {
        while (true)
        {
            _window->Update();
        }
    }

    auto Application::OnWindowEvent(const SWindowEvent& event) -> void {}
}
