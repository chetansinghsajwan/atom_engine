#pragma once
#include "Atom/CoreAll.h"

namespace Atom::Engine
{
    class WindowCoords
    {
    public:
        i32 x;
        i32 y;
    };

    inline auto operator-(const WindowCoords& lhs, const WindowCoords& rhs) -> WindowCoords
    {
        return { lhs.x - rhs.x, lhs.y - rhs.y };
    }

    enum class EWindowEventType
    {
        Resize,
        Reposition,
        Close,
    };

    class WindowEvent
    {
    public:
        WindowEvent(EWindowEventType eventType)
            : eventType(eventType)
        {}

    public:
        const EWindowEventType eventType;
    };

    class WindowResizeEvent: public WindowEvent
    {
    public:
        WindowResizeEvent(WindowCoords size, WindowCoords delta)
            : size(size)
            , delta(delta)
            , WindowEvent(EWindowEventType::Resize)
        {}

    public:
        WindowCoords size;
        WindowCoords delta;
    };

    class WindowRepositionEvent: public WindowEvent
    {
    public:
        WindowRepositionEvent(WindowCoords position, WindowCoords delta)
            : position(position)
            , delta(delta)
            , WindowEvent(EWindowEventType::Reposition)
        {}

    public:
        WindowCoords position;
        WindowCoords delta;
    };

    class WindowCloseEvent: public WindowEvent
    {
    public:
        WindowCloseEvent()
            : WindowEvent(EWindowEventType::Close)
        {}
    };

    class Window
    {
    public:
        Window(IEvent<const WindowEvent&>& event)
            : OnEvent{ event }
        {}

    public:
        virtual ~Window() = default;

        virtual auto Update() -> void = 0;

        virtual auto GetSize() const -> WindowCoords = 0;
        virtual auto SetSize(WindowCoords size) -> void = 0;

        virtual auto GetPos() const -> WindowCoords = 0;
        virtual auto SetPos(WindowCoords pos) -> void = 0;

        virtual auto GetNative() const -> void* = 0;

    public:
        IEvent<const WindowEvent&>& OnEvent;
    };
}
