export module atom.engine:application;
import :window;
import :window_manager;
import atom.core;

namespace atom::engine
{
    export class application
    {
    public:
        application()
        {
            window_props window_props{
                .window_name = "sandbox", .window_size = {1920, 1080}
            };

            _window = window_manager::create_window(window_props);
            contracts::debug_asserts(_window != nullptr);

            _window->event +=
                [this](const window_event& event) { this->on_window_event(event); };
        }

        virtual ~application()
        {
            if (_window != nullptr)
            {
                window_manager::close_window(_window);
            }
        }

    public:
        virtual auto run() -> void
        {
            while (true)
            {
                _window->update();
            }
        }

        virtual auto on_window_event(const window_event& event) -> void {}

    protected:
        window* _window;
    };
}
