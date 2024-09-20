#include "atom/engine/application.h"
#include "imgui/imgui_layer.h"

namespace atom::engine
{
    application::application()
        : _window(nullptr)
        , _layers()
        , _layer(nullptr)
        , _should_run(true)
    {
        contracts::debug_expects(get() == nullptr, "an appication instance already exists.");
        _s_app = this;

        window_props window_props{
            .window_name = "sandbox", .window_size = {1920, 1080}
        };

        _window = window_manager::create_window(window_props);
        contracts::debug_asserts(_window != nullptr);

        _window->subscribe_event(this);

        _layer = unique_ptr<layer>(new imgui_layer());
        _layers.push_layer(_layer.to_unwrapped());
    }

    application::~application()
    {
        if (_window != nullptr)
        {
            _window->unsubscribe_event(this);
            window_manager::destroy_window(_window);
        }

        _layers.pop_layer(_layer.to_unwrapped());
    }

    auto application::run() -> void
    {
        while (_should_run)
        {
            _window->update();
            _layers.update_layers();
        }
    }

    auto application::handle(window_event& event) -> void
    {
        switch (event.event_type)
        {
            case window_event_type::destroy:
            {
                _should_run = false;
                break;
            }

            default: break;
        }
    }
}
