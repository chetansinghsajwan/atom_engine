export module atom.engine:application;
import :window;
import :window_manager;
import :layer_stack;
import :imgui_layer;
import atom.core;

namespace atom::engine
{
    export class application
    {
    public:
        application()
        {
            contracts::debug_expects(get() == nullptr, "an appication instance already exists.");
            _s_app = this;

            window_props window_props{
                .window_name = "sandbox", .window_size = {1920, 1080}
            };

            _window = window_manager::create_window(window_props);
            contracts::debug_asserts(_window != nullptr);

            _window->event += [this](const window_event& event) { this->on_window_event(event); };

            _imgui_layer = make_unique<imgui_layer>();
            _layers.push_layer(_imgui_layer);
        }

        virtual ~application()
        {
            if (_window != nullptr)
            {
                window_manager::close_window(_window);
            }

            _layers.pop_layer(_imgui_layer);
        }

    public:
        static auto get() -> application*
        {
            return _s_app;
        }

    public:
        virtual auto run() -> void
        {
            while (true)
            {
                _window->update();
            }
        }

        auto get_window() const -> window*
        {
            return _window;
        }

        virtual auto on_window_event(const window_event& event) -> void {}

    protected:
        window* _window;
        layer_stack _layers;
        unique_ptr<imgui_layer> _imgui_layer;

    private:
        static inline application* _s_app;
    };

    extern "C++" auto get_application_window() -> window*
    {
        return application::get()->get_window();
    }
}
