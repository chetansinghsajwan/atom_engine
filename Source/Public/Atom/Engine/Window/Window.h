#pragma once
#include "Atom/CoreAll.h"

namespace Atom::Engine
{
    class SWindowCoords
    {
    public:
        i32 x;
        i32 y;
    };

    inline auto operator-(const SWindowCoords& lhs, const SWindowCoords& rhs) -> SWindowCoords
    {
        return { lhs.x - rhs.x, lhs.y - rhs.y };
    }

    enum class EWindowEventType
    {
        Resize,
        Reposition,
        Close,
    };

    class SWindowEvent
    {
    public:
        SWindowEvent(EWindowEventType eventType)
            : eventType(eventType)
        {}

    public:
        const EWindowEventType eventType;
    };

    class SWindowResizeEvent: public SWindowEvent
    {
    public:
        SWindowResizeEvent(SWindowCoords size, SWindowCoords delta)
            : size(size)
            , delta(delta)
            , SWindowEvent(EWindowEventType::Resize)
        {}

    public:
        SWindowCoords size;
        SWindowCoords delta;
    };

    class SWindowRepositionEvent: public SWindowEvent
    {
    public:
        SWindowRepositionEvent(SWindowCoords position, SWindowCoords delta)
            : position(position)
            , delta(delta)
            , SWindowEvent(EWindowEventType::Reposition)
        {}

    public:
        SWindowCoords position;
        SWindowCoords delta;
    };

    class SWindowCloseEvent: public SWindowEvent
    {
    public:
        SWindowCloseEvent()
            : SWindowEvent(EWindowEventType::Close)
        {}
    };

    class Window
    {
    public:
        Window(IEvent<const SWindowEvent&>& event)
            : OnEvent{ event }
        {}

    public:
        virtual ~Window() = default;

        virtual auto Update() -> void = 0;

        virtual auto GetSize() const -> SWindowCoords = 0;
        virtual auto SetSize(SWindowCoords size) -> void = 0;

        virtual auto GetPos() const -> SWindowCoords = 0;
        virtual auto SetPos(SWindowCoords pos) -> void = 0;

        virtual auto GetNative() const -> void* = 0;

    public:
        IEvent<const SWindowEvent&>& OnEvent;
    };
}
