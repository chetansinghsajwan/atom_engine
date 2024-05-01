#include "atom/core/contracts.h"
#include "atom/engine/application.h"
#include "atom/engine/window/window_manager.h"
#include "atom/engine/inputs/keyboard.h"
#include "atom/engine/inputs/mouse.h"
#include "atom/engine/inputs/input_manager.h"
#include "atom/engine/logging.h"
#include "engine/imgui/imgui_layer.h"
#include "engine/opengl/opengl_shader.h"
#include "engine/rendering/buffer_layout.h"
#include "engine/rendering/index_buffer.h"
#include "engine/rendering/vertex_buffer.h"
#include "engine/rendering/renderer.h"
#include "GLFW/glfw3.h"
#include <memory>
#include <cstdint>

namespace atom::engine
{
    application::application()
        : _window(nullptr)
        , _layers()
        , _layer(nullptr)
        , _last_frame_time(0)
        , _should_run(true)
    {
        ATOM_DEBUG_EXPECTS(get() == nullptr, "an appication instance already exists.");
        _s_app = this;

        // window setup

        window_props window_props{
            .window_name = "sandbox", .window_size = { 1920, 1080 }
        };

        _window = window_manager::create_window(window_props);
        ATOM_DEBUG_EXPECTS(_window != nullptr);

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

        // layer setup

        _layer = new imgui_layer();
        _layers.push_layer(_layer);
    }

    application::~application()
    {
        if (_window != nullptr)
        {
            _window->unsubscribe_event(this);
            window_manager::destroy_window(_window);
        }

        _layers.pop_layer(_layer);
        delete _layer;
    }

    auto application::run() -> void
    {
        while (_should_run)
        {
            float time = glfwGetTime();
            float delta_time = time - _last_frame_time;
            _last_frame_time = time;

            if (!_window->is_minimized())
            {
                for (layer* layer : _layers.get_layers())
                    layer->on_update(time_stemp(delta_time));
            }

            class imgui_layer* imgui_layer = (class imgui_layer*)_layer;

            imgui_layer->begin_render();
            for (layer* layer : _layers.get_layers())
            {
                layer->on_imgui_render();
            }
            imgui_layer->end_render();

            _window->update();
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

            case window_event_type::resize:
            {
                _on_window_resize_event(reinterpret_cast<window_resize_event&>(event));
                break;
            }

            default: break;
        }
    }

    auto application::_on_window_resize_event(window_resize_event& event) -> void
    {
        if (_window->is_minimized())
            return;

        renderer::on_window_resize(event.size.x, event.size.y);
    }

    auto application::handle(keyboard_event& event) -> void {}

    auto application::handle(mouse_event& event) -> void {}
}
