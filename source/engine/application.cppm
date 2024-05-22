export module atom.engine:application;

import atom.core;
import :layers;
import :windows;
import :inputs;
import :rendering;

namespace atom::engine
{
    export class application
        : public window_event_listener
        , public keyboard_event_listener
        , public mouse_event_listener
    {
    public:
        application(string_view name)
            : _name(name)
            , _window(nullptr)
            , _layers()
            , _layer(nullptr)
            , _last_frame_time(0)
            , _should_run(true)
        {
            contract_debug_expects(get() == nullptr, "an appication instance already exists.");
            _s_app = this;

            // window setup

            window_props window_props{
                .window_name = name, .window_size = { 1920, 1080 }
            };

            _window = window_manager::create_window(window_props);
            contract_debug_expects(_window != nullptr);

            _window->subscribe_event(this);

            renderer::initialize();

            // inputs event setup

            for (input_device* device : input_manager::get_devices())
            {
                if (device->get_type() == input_device_type::keyboard)
                {
                    reinterpret_cast<keyboard*>(device)->subscribe_event(this);
                }
                else if (device->get_type() == input_device_type::mouse)
                {
                    reinterpret_cast<mouse*>(device)->subscribe_event(this);
                }
            }

            _setup_layer();
        }

        virtual ~application()
        {
            if (_window != nullptr)
            {
                _window->unsubscribe_event(this);
                window_manager::destroy_window(_window);
            }

            _layers.pop_layer(_layer);
            delete _layer;
        }

    public:
        static auto get() -> application*
        {
            return _s_app;
        }

        virtual auto stop() -> void
        {
            _should_run = false;
        }

        virtual auto run() -> void
        {
            _run();
        }

        auto get_window() const -> window*
        {
            return _window;
        }

        auto push_layer(class layer* layer) -> void
        {
            _layers.push_layer(layer);
        }

    private:
        virtual auto handle(window_event& event) -> void override
        {
            switch (event.event_type)
            {
                case window_event_type::destroy:
                {
                    _should_run = false;
                    break;
                }

                case window_event_type::resize:
                {
                    _on_window_resize_event(reinterpret_cast<window_resize_event&>(event));
                    break;
                }

                default: break;
            }
        }

        auto _on_window_resize_event(window_resize_event& event) -> void
        {
            if (_window->is_minimized())
                return;

            renderer::on_window_resize(event.size.x, event.size.y);
        }

        virtual auto handle(keyboard_event& event) -> void override {}

        virtual auto handle(mouse_event& event) -> void override {}

        auto _setup_layer() -> void;

        auto _run() -> void;

    private:
        string _name;
        window* _window;
        layer_stack _layers;
        layer* _layer;
        f32 _last_frame_time;
        bool _should_run;

    private:
        static inline application* _s_app;
    };
};
