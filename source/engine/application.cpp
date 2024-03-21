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
#include "glad/glad.h"
#include <memory>
#include <cstdint>

namespace atom::engine
{
    constexpr auto convert_shader_data_type_atom_to_opengl(shader_data_type type) -> GLenum
    {
        switch (type)
        {
            case shader_data_type::boolean: return GL_BOOL;
            case shader_data_type::int1:    return GL_INT;
            case shader_data_type::int2:    return GL_INT;
            case shader_data_type::int3:    return GL_INT;
            case shader_data_type::int4:    return GL_INT;
            case shader_data_type::float1:  return GL_FLOAT;
            case shader_data_type::float2:  return GL_FLOAT;
            case shader_data_type::float3:  return GL_FLOAT;
            case shader_data_type::float4:  return GL_FLOAT;
            case shader_data_type::mat3:    return GL_FLOAT;
            case shader_data_type::mat4:    return GL_FLOAT;
            default:
            {
                ATOM_PANIC("invalid shader_data_type.");
                return 0;
            }
        }
    }

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

        glGenVertexArrays(1, &_vertex_array);
        glBindVertexArray(_vertex_array);

        // clang-format off
        float vertices[] =
        {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };
        // clang-format on
        _vertex_buffer = std::unique_ptr<vertex_buffer>(
            vertex_buffer::create(vertices, sizeof(vertices) / sizeof(float)));

        _vertex_buffer->set_layout({
            {shader_data_type::float3,  "a_position"},
            { shader_data_type::float4, "a_color"   }
        });

        const buffer_layout& layout = _vertex_buffer->get_layout();
        array_view<buffer_element> layout_elements = layout.get_elements();
        for (usize i = 0; i < layout_elements.get_count(); i++)
        {
            const auto& elem = layout_elements[i];

            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, elem.get_component_count(),
                convert_shader_data_type_atom_to_opengl(elem.type),
                elem.is_normalized ? GL_TRUE : GL_FALSE, layout.get_stride(),
                (const void*)elem.offset);
        }

        uint32_t indices[3] = { 0, 1, 2 };
        _index_buffer = std::unique_ptr<index_buffer>(
            index_buffer::create(indices, sizeof(indices) / sizeof(uint32_t)));

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
    }

    auto application::run() -> void
    {
        while (_should_run)
        {
            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            _shader->bind();
            glBindVertexArray(_vertex_array);
            glDrawElements(GL_TRIANGLES, _index_buffer->get_count(), GL_UNSIGNED_INT, nullptr);

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
