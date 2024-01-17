export module atom.engine:application;
import :window;
import :window_manager;

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

    Application::Application()
    {
        WindowProps windowProps{
            .windowName = MakeRange("Sandbox"), .windowSize = {1920, 1080}
        };

        _window = WindowManger::CreateWindow(windowProps);
        Contracts::DebugAsserts(_window != nullptr);

        _window->OnEvent += [this](const WindowEvent& event) { this->OnWindowEvent(event); };
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

    auto Application::OnWindowEvent(const WindowEvent& event) -> void {}
}
