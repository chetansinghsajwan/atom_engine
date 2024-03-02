#include "atom/engine/application.h"
#include "imgui_layer.h"

namespace atom::engine
{
    application::application()
    {
        contracts::debug_expects(get() == nullptr, "an appication instance already exists.");
        _s_app = this;

        window_props window_props{
            .window_name = "sandbox", .window_size = {1920, 1080}
        };

        _window = window_manager::create_window(window_props);
        contracts::debug_asserts(_window != nullptr);

        _window->event += [this](const window_event& event) { this->on_window_event(event); };

        _layer = unique_ptr<layer>(new imgui_layer());
        _layers.push_layer(_layer.to_unwrapped());
    }

    application::~application()
    {
        if (_window != nullptr)
        {
            window_manager::destroy_window(_window);
        }

        _layers.pop_layer(_layer.to_unwrapped());
    }

    auto application::run() -> void
    {
        while (true)
        {
            _window->update();
            _layers.update_layers();
        }
    }

    auto application::on_window_event(const window_event& event) -> void {}

    auto get_application_window() -> window*
    {
        return application::get()->get_window();
    }
}
