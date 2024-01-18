export module atom.engine:window;
import atom.core;

namespace Atom::Engine
{
    export class WindowProps
    {
    public:
        String windowName;
        WindowCoords windowSize;
    };

    export class WindowCoords
    {
    public:
        i32 x;
        i32 y;
    };

    export inline auto operator-(const WindowCoords& lhs, const WindowCoords& rhs) -> WindowCoords
    {
        return { lhs.x - rhs.x, lhs.y - rhs.y };
    }

    export enum class EWindowEventType
    {
        Resize,
        Reposition,
        Close,
    };

    export class WindowEvent
    {
    public:
        WindowEvent(EWindowEventType eventType)
            : eventType(eventType)
        {}

    public:
        const EWindowEventType eventType;
    };

    export class WindowResizeEvent: public WindowEvent
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

    export class WindowRepositionEvent: public WindowEvent
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

    export class WindowCloseEvent: public WindowEvent
    {
    public:
        WindowCloseEvent()
            : WindowEvent(EWindowEventType::Close)
        {}
    };

    export class Window
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
