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

        // window setup

        window_props window_props{
            .window_name = "sandbox", .window_size = {1920, 1080}
        };

        _window = window_manager::create_window(window_props);
        ATOM_DEBUG_EXPECTS(_window != nullptr);

        _window->subscribe_event(this);

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

        // renderer setup

        _vertex_array = std::unique_ptr<vertex_array>(vertex_array::create());

        // clang-format off
        float vertices[] =
        {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };
        // clang-format on

        vertex_buffer* vbuffer = vertex_buffer::create(vertices, sizeof(vertices) / sizeof(float));
        vbuffer->set_layout({
            {shader_data_type::float3,  "a_position"},
            { shader_data_type::float4, "a_color"   }
        });
        _vertex_array->add_vertex_buffer(&*vbuffer);

        uint32_t indices[3] = { 0, 1, 2 };
        index_buffer* ibuffer = index_buffer::create(indices, sizeof(indices) / sizeof(uint32_t));
        _vertex_array->set_index_buffer(&*ibuffer);

        const string_view vertex_shader_source = R"(
            #version 330 core

            layout(location = 0) in vec3 a_position;
            layout(location = 1) in vec4 a_color;

			out vec3 v_position;
			out vec4 v_color;

            void main()
            {
                v_position = a_position;
                v_color = a_color;
                gl_Position = vec4(a_position, 1.0);
            }
        )";

        const string_view fragment_shader_source = R"(
            #version 330 core

            layout(location = 0) out vec4 color;
			in vec3 v_position;
			in vec4 v_color;

            void main()
            {
                color = v_color;
            }
        )";

        _shader = std::make_unique<opengl_shader>(vertex_shader_source, fragment_shader_source);
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

        delete _vertex_array->get_index_buffer();
        for (const vertex_buffer* buffer : _vertex_array->get_vertex_buffers())
        {
            delete buffer;
        }
    }

    auto application::run() -> void
    {
        while (_should_run)
        {
            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            render_command::set_clear_color({ 0.1f, 0.1f, 0.1f, 1 });
            render_command::clear_color();

            renderer::begin_scene();

            _shader->bind();
            renderer::submit(&*_vertex_array);

            renderer::end_scene();

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
