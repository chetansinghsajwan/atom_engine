import atom.core;
import atom.logging;

#include "opengl_index_buffer.h"
#include "glad/glad.h"

namespace atom::engine
{
    opengl_index_buffer::opengl_index_buffer(uint32_t* indices, u32 count)
        : _renderer_id(0)
        , _count(count)
    {
        glCreateBuffers(1, &_renderer_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _renderer_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    opengl_index_buffer::~opengl_index_buffer()
    {
        glDeleteBuffers(1, &_renderer_id);
    }

    auto opengl_index_buffer::bind() const -> void
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _renderer_id);
    }

    auto opengl_index_buffer::unbind() const -> void
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    auto opengl_index_buffer::get_count() const -> u32
    {
        return _count;
    }
}
