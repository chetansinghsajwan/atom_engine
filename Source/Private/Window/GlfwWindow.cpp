module;
#include "GLFW/glfw3.h"

export module atom.engine:window.glfw;
import atom.core;
import atom.logging;
import :window;
import :window_manager;

using namespace Atom;
using namespace Atom::Logging;

namespace Atom::Engine
{
    class GlfwWindowCoords
    {
    public:
        i32 x;
        i32 y;
    };

    class GlfwWindowCoordsConverter
    {
    public:
        static constexpr auto ToGLFW(WindowCoords coords) -> GlfwWindowCoords
        {
            coords.x = coords.x.clamp(i32::Min(), i32::Max());
            coords.y = coords.y.clamp(i32::Min(), i32::Max());

            return { coords.x, coords.y };
        };

        static constexpr auto FromGLFW(GlfwWindowCoords coords) -> WindowCoords
        {
            coords.x = coords.x.clamp(i32::Min(), i32::Max());
            coords.y = coords.y.clamp(i32::Min(), i32::Max());

            return { coords.x, coords.y };
        };
    };

    class GlfwWindow: public Window
    {
    public:
        GlfwWindow(const WindowProps& props);
        ~GlfwWindow();

        virtual auto Update() -> void override;

        virtual auto SetPos(WindowCoords size) -> void override;
        virtual auto GetPos() const -> WindowCoords override;
        virtual auto UpdatePos() -> WindowCoords;

        virtual auto SetSize(WindowCoords size) -> void override;
        virtual auto GetSize() const -> WindowCoords override;
        virtual auto UpdateSize() -> WindowCoords;

        virtual auto GetNative() const -> void* override final;

        auto SetVSync(bool enable) -> void;
        auto GetVSync() const -> bool;

        auto GetNativeGLFW() const -> GLFWwindow*
        {
            return _glfwWindow;
        }

    protected:
        GLFWwindow* _glfwWindow;
        WindowCoords _windowPos;
        WindowCoords _windowSize;
        bool _windowVSync;

        EventSource<const WindowEvent&> _windowEventSource;
    };

    GlfwWindow::GlfwWindow(const WindowProps& props)
        : Window(_windowEventSource)
    {
        GlfwWindowCoords glfwWindowSize = GlfwWindowCoordsConverter::ToGLFW(props.windowSize);

        // TODO: Requires encoding conversion.
        _glfwWindow = glfwCreateWindow(glfwWindowSize.x, glfwWindowSize.y,
            props.windowName.data().asUnsafe<char>().unwrap(), nullptr, nullptr);

        glfwMakeContextCurrent(_glfwWindow);
        glfwSetWindowUserPointer(_glfwWindow, this);

        glfwSetWindowPosCallback(_glfwWindow, [](GLFWwindow* glfwWindow, _i32 xpos, _i32 ypos) {
            GlfwWindow& window = *reinterpret_cast<GlfwWindow*>(
                glfwGetWindowUserPointer(glfwWindow));

            WindowCoords oldPos = window._windowPos;
            WindowCoords newPos = GlfwWindowCoordsConverter::FromGLFW({ xpos, ypos });
            window._windowPos = newPos;

            window._windowEventSource.Dispatch(WindowRepositionEvent(newPos, newPos - oldPos));
        });

        glfwSetWindowSizeCallback(_glfwWindow, [](GLFWwindow* glfwWindow, _i32 width, _i32 height) {
            GlfwWindow& window = *reinterpret_cast<GlfwWindow*>(
                glfwGetWindowUserPointer(glfwWindow));

            WindowCoords oldSize = window._windowSize;
            WindowCoords newSize = GlfwWindowCoordsConverter::FromGLFW({ width, height });
            window._windowSize = newSize;

            window._windowEventSource.Dispatch(WindowResizeEvent(newSize, newSize - oldSize));
        });

        glfwSetWindowCloseCallback(_glfwWindow, [](GLFWwindow* glfwWindow) {
            GlfwWindow& window =
                *reinterpret_cast<GlfwWindow*>(glfwGetWindowUserPointer(glfwWindow));

            window._windowEventSource.Dispatch(WindowCloseEvent());
        });

        UpdatePos();
        UpdateSize();
        SetVSync(true);
    }

    GlfwWindow::~GlfwWindow()
    {
        glfwDestroyWindow(_glfwWindow);
    }

    auto GlfwWindow::Update() -> void
    {
        glfwPollEvents();
        glfwSwapBuffers(_glfwWindow);
    }

    auto GlfwWindow::SetPos(WindowCoords pos) -> void
    {
        GlfwWindowCoords glfwPos = GlfwWindowCoordsConverter::ToGLFW(pos);

        glfwSetWindowPos(_glfwWindow, glfwPos.x, glfwPos.y);
        _windowPos = GlfwWindowCoordsConverter::FromGLFW(glfwPos);
    }

    auto GlfwWindow::GetPos() const -> WindowCoords
    {
        return _windowPos;
    }

    auto GlfwWindow::UpdatePos() -> WindowCoords
    {
        int x;
        int y;
        glfwGetWindowPos(_glfwWindow, &x, &y);

        return GlfwWindowCoordsConverter::FromGLFW(GlfwWindowCoords{ x, y });
    }

    auto GlfwWindow::SetSize(WindowCoords size) -> void
    {
        GlfwWindowCoords glfwSize = GlfwWindowCoordsConverter::ToGLFW(size);

        glfwSetWindowSize(_glfwWindow, glfwSize.x, glfwSize.y);
        _windowSize = GlfwWindowCoordsConverter::FromGLFW(glfwSize);
    }

    auto GlfwWindow::GetSize() const -> WindowCoords
    {
        return _windowSize;
    }

    auto GlfwWindow::UpdateSize() -> WindowCoords
    {
        int x;
        int y;
        glfwGetWindowSize(_glfwWindow, &x, &y);

        _windowSize = GlfwWindowCoordsConverter::FromGLFW(GlfwWindowCoords{ x, y });
        return _windowSize;
    }

    auto GlfwWindow::SetVSync(bool enable) -> void
    {
        glfwSwapInterval(enable ? 1 : 0);
        _windowVSync = enable;
    }

    auto GlfwWindow::GetVSync() const -> bool
    {
        return _windowVSync;
    }

    auto GlfwWindow::GetNative() const -> void*
    {
        return _glfwWindow;
    }
}
