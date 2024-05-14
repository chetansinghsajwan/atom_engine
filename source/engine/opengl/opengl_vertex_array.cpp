import atom.core;
import atom.logging;

#include "opengl_vertex_array.h"
#include "glad/glad.h"

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

    opengl_vertex_array::opengl_vertex_array()
    {
        glCreateVertexArrays(1, &_renderer_id);
    }

    opengl_vertex_array::~opengl_vertex_array()
    {
        glDeleteVertexArrays(1, &_renderer_id);
    }

    auto opengl_vertex_array::bind() -> void
    {
        glBindVertexArray(_renderer_id);
    }

    auto opengl_vertex_array::unbind() -> void
    {
        glBindVertexArray(0);
    }

    auto opengl_vertex_array::add_vertex_buffer(vertex_buffer* buffer) -> void
    {
        ATOM_DEBUG_EXPECTS(buffer != nullptr);
        ATOM_EXPECTS(
            not buffer->get_layout().get_elements().is_empty(), "vertex_buffer has no layout.");

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

    auto opengl_vertex_array::get_vertex_buffers() const -> array_view<vertex_buffer*>
    {
        return _vertex_buffers;
    }

    auto opengl_vertex_array::set_index_buffer(index_buffer* buffer) -> void
    {
        ATOM_DEBUG_EXPECTS(buffer != nullptr);

        glBindVertexArray(_renderer_id);
        buffer->bind();

        _index_buffer = buffer;
    }

    auto opengl_vertex_array::get_index_buffer() const -> index_buffer*
    {
        return _index_buffer;
    }
}
