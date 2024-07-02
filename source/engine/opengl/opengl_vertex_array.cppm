module;
#include "glad/glad.h"

export module atom.engine:opengl.vertex_array;

import atom_core;
import :rendering.vertex_array;

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
            case shader_data_type::f32mat4: return GL_FLOAT;
            default:
            {
                contract_panic("invalid shader_data_type.");
                return 0;
            }
        }
    }

    class opengl_vertex_array: public vertex_array
    {
    public:
        opengl_vertex_array()
        {
            glCreateVertexArrays(1, &_renderer_id);
        }

        virtual ~opengl_vertex_array()
        {
            glDeleteVertexArrays(1, &_renderer_id);
        }

    public:
        virtual auto bind() -> void override
        {
            glBindVertexArray(_renderer_id);
        }

        virtual auto unbind() -> void override
        {
            glBindVertexArray(0);
        }

        virtual auto add_vertex_buffer(vertex_buffer* buffer) -> void override
        {
            contract_debug_expects(buffer != nullptr);
            contract_expects(buffer->get_layout().get_elements() | ranges::is_not_empty(),
                "vertex_buffer has no layout.");

            glBindVertexArray(_renderer_id);
            buffer->bind();

            const buffer_layout& layout = buffer->get_layout();
            array_view<buffer_element> elems = layout.get_elements();

            for (usize i = 0; i < elems.get_count(); i++)
            {
                const auto& elem = elems[i];

                glEnableVertexAttribArray(i);
                glVertexAttribPointer(i, elem.get_component_count(),
                    convert_shader_data_type_atom_to_opengl(elem.type),
                    elem.is_normalized ? GL_TRUE : GL_FALSE, layout.get_stride(),
                    (const void*)(usize)elem.offset);
            }

            _vertex_buffers.emplace_back(buffer);
        }

        virtual auto get_vertex_buffers() const -> array_view<vertex_buffer*> override
        {
            return _vertex_buffers;
        }

        virtual auto set_index_buffer(index_buffer* buffer) -> void override
        {
            contract_debug_expects(buffer != nullptr);

            glBindVertexArray(_renderer_id);
            buffer->bind();

            _index_buffer = buffer;
        }

        virtual auto get_index_buffer() const -> index_buffer* override
        {
            return _index_buffer;
        }

    private:
        GLuint _renderer_id;
        dynamic_array<vertex_buffer*> _vertex_buffers;
        index_buffer* _index_buffer;
    };
}
