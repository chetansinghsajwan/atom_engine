export module atom.engine:application;
import :window;
import :window_manager;
import atom.core;

namespace atom::engine
{
    export class application
    {
    public:
        application();
        virtual ~application();

    public:
        virtual auto run() -> void;

        virtual auto on_window_event(const window_event& event) -> void;

    protected:
        window* _window;
    };

    application::application()
    {
        window_props window_props{
            .window_name = make_range("sandbox"), .window_size = {1920, 1080}
        };

        _window = window_manager::create_window(window_props);
        contracts::debug_asserts(_window != nullptr);

        _window->on_event += [this](const window_event& event) { this->on_window_event(event); };
    }

    application::~application()
    {
        if (_window != nullptr)
        {
            window_manager::close_window(_window);
        }
    }

    auto application::run() -> void
    {
        while (true)
        {
            _window->update();
        }
    }

    auto application::on_window_event(const window_event& event) -> void {}
}
