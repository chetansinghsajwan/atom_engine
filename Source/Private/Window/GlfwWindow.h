#pragma once
#include "GLFW/glfw3.h"

#include "Atom/CoreAll.h"
#include "Atom/Engine/Window/WindowManager.h"

namespace Atom::Engine
{
    class GlfwSWindowCoords
    {
    public:
        i32 x;
        i32 y;
    };

    class GlfwWindowCoordsConverter
    {
    public:
        static constexpr auto ToGLFW(SWindowCoords coords) -> GlfwSWindowCoords
        {
            coords.x = coords.x.clamp(i32::Min(), i32::Max());
            coords.y = coords.y.clamp(i32::Min(), i32::Max());

            return { coords.x, coords.y };
        };

        static constexpr auto FromGLFW(GlfwSWindowCoords coords) -> SWindowCoords
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

        virtual auto SetPos(SWindowCoords size) -> void override;
        virtual auto GetPos() const -> SWindowCoords override;
        virtual auto UpdatePos() -> SWindowCoords;

        virtual auto SetSize(SWindowCoords size) -> void override;
        virtual auto GetSize() const -> SWindowCoords override;
        virtual auto UpdateSize() -> SWindowCoords;

        virtual auto GetNative() const -> void* override final;

        auto SetVSync(bool enable) -> void;
        auto GetVSync() const -> bool;

        auto GetNativeGLFW() const -> GLFWwindow*
        {
            return _glfwWindow;
        }

    protected:
        GLFWwindow* _glfwWindow;
        SWindowCoords _windowPos;
        SWindowCoords _windowSize;
        bool _windowVSync;

        EventSource<const SWindowEvent&> _windowEventSource;
    };
}
