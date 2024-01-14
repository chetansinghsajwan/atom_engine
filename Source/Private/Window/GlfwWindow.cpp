#include "Window/GlfwWindow.h"
#include "Atom/Logging.h"

using namespace Atom::Logging;

namespace Atom::Engine
{
    GlfwWindow::GlfwWindow(const WindowProps& props)
        : Window(_windowEventSource)
    {
        GlfwSWindowCoords glfwWindowSize = GlfwWindowCoordsConverter::ToGLFW(props.windowSize);

        // TODO: Requires encoding conversion.
        _glfwWindow = glfwCreateWindow(glfwWindowSize.x, glfwWindowSize.y,
            props.windowName.data().asUnsafe<char>().unwrap(), nullptr, nullptr);

        glfwMakeContextCurrent(_glfwWindow);
        glfwSetWindowUserPointer(_glfwWindow, this);

        glfwSetWindowPosCallback(_glfwWindow, [](GLFWwindow* glfwWindow, _i32 xpos, _i32 ypos) {
            GlfwWindow& window = *reinterpret_cast<GlfwWindow*>(
                glfwGetWindowUserPointer(glfwWindow));

            SWindowCoords oldPos = window._windowPos;
            SWindowCoords newPos = GlfwWindowCoordsConverter::FromGLFW({ xpos, ypos });
            window._windowPos = newPos;

            window._windowEventSource.Dispatch(SWindowRepositionEvent(newPos, newPos - oldPos));
        });

        glfwSetWindowSizeCallback(_glfwWindow, [](GLFWwindow* glfwWindow, _i32 width, _i32 height) {
            GlfwWindow& window = *reinterpret_cast<GlfwWindow*>(
                glfwGetWindowUserPointer(glfwWindow));

            SWindowCoords oldSize = window._windowSize;
            SWindowCoords newSize = GlfwWindowCoordsConverter::FromGLFW({ width, height });
            window._windowSize = newSize;

            window._windowEventSource.Dispatch(SWindowResizeEvent(newSize, newSize - oldSize));
        });

        glfwSetWindowCloseCallback(_glfwWindow, [](GLFWwindow* glfwWindow) {
            GlfwWindow& window =
                *reinterpret_cast<GlfwWindow*>(glfwGetWindowUserPointer(glfwWindow));

            window._windowEventSource.Dispatch(SWindowCloseEvent());
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

    auto GlfwWindow::SetPos(SWindowCoords pos) -> void
    {
        GlfwSWindowCoords glfwPos = GlfwWindowCoordsConverter::ToGLFW(pos);

        glfwSetWindowPos(_glfwWindow, glfwPos.x, glfwPos.y);
        _windowPos = GlfwWindowCoordsConverter::FromGLFW(glfwPos);
    }

    auto GlfwWindow::GetPos() const -> SWindowCoords
    {
        return _windowPos;
    }

    auto GlfwWindow::UpdatePos() -> SWindowCoords
    {
        int x;
        int y;
        glfwGetWindowPos(_glfwWindow, &x, &y);

        return GlfwWindowCoordsConverter::FromGLFW(GlfwSWindowCoords{ x, y });
    }

    auto GlfwWindow::SetSize(SWindowCoords size) -> void
    {
        GlfwSWindowCoords glfwSize = GlfwWindowCoordsConverter::ToGLFW(size);

        glfwSetWindowSize(_glfwWindow, glfwSize.x, glfwSize.y);
        _windowSize = GlfwWindowCoordsConverter::FromGLFW(glfwSize);
    }

    auto GlfwWindow::GetSize() const -> SWindowCoords
    {
        return _windowSize;
    }

    auto GlfwWindow::UpdateSize() -> SWindowCoords
    {
        int x;
        int y;
        glfwGetWindowSize(_glfwWindow, &x, &y);

        _windowSize = GlfwWindowCoordsConverter::FromGLFW(GlfwSWindowCoords{ x, y });
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
