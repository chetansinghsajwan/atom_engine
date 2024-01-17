#pragma once
#include "GLFW/glfw3.h"

#include "Atom/CoreAll.h"
#include "Atom/Engine/Window/WindowManager.h"

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
}
