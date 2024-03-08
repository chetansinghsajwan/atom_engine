#include "atom/core/contracts.h"
#include "atom/engine/application.h"
#include "atom/engine/window/window_manager.h"
#include "atom/engine/inputs/keyboard.h"
#include "atom/engine/inputs/mouse.h"
#include "atom/engine/inputs/input_manager.h"
#include "engine/imgui/imgui_layer.h"
#include "engine/opengl/opengl_shader.h"
#include "engine/rendering/index_buffer.h"
#include "engine/rendering/vertex_buffer.h"
#include "glad/glad.h"
#include <memory>
#include <cstdint>

namespace atom::engine
{
    application::application()
        : _window(nullptr)
        , _layers()
        , _layer(nullptr)
        , _should_run(true)
    {
        ATOM_DEBUG_EXPECTS(get() == nullptr, "an appication instance already exists.");
        _s_app = this;

        window_props window_props{
            .window_name = "sandbox", .window_size = {1920, 1080}
        };

        _window = window_manager::create_window(window_props);
        ATOM_DEBUG_EXPECTS(_window != nullptr);

        _window->subscribe_event(this);

        _layer = new imgui_layer();
        _layers.push_layer(_layer);

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

        const string_view vertex_shader_source = R"(
            #version 330 core

            layout(location = 0) in vec3 a_postition;

            void main()
            {
                gl_Position = vec4(a_position, 1.0);
            }
        )";

        const string_view fragment_shader_source = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            void main()
            {
                color = vec4(0.8, 0.2, 0.3, 1.0);
            }
        )";

        _shader = std::make_unique<opengl_shader>(vertex_shader_source, fragment_shader_source);

        float vertices[3 * 3] = { -0.5f, -0.5f, +0.0f, +0.5f, -0.5f, +0.0f, +0.0f, +0.5f, +0.0f };
        _vertex_buffer = std::unique_ptr<vertex_buffer>(
            vertex_buffer::create(vertices, sizeof(vertices) / sizeof(float)));

        uint32_t indices[3] = { 0, 1, 2 };
        _index_buffer = std::unique_ptr<index_buffer>(
            index_buffer::create(indices, sizeof(indices) / sizeof(uint32_t)));
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
            glClear(GL_COLOR_BUFFER_BIT);

            _shader->bind();

            for (layer* layer : _layers.get_layers())
                layer->on_update();

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

            default: break;
        }
    }

    auto application::handle(keyboard_event& event) -> void {}

    auto application::handle(mouse_event& event) -> void {}
}
