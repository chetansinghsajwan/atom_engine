#include "opengl_vertex_buffer.h"
#include "engine/rendering/buffer_layout.h"
#include "glad/glad.h"

namespace atom::engine
{
    opengl_vertex_buffer::opengl_vertex_buffer(u32 size)
        : _renderer_id(0)
        , _count(size)
    {
        glCreateBuffers(1, &_renderer_id);
        glBindBuffer(GL_ARRAY_BUFFER, _renderer_id);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    opengl_vertex_buffer::opengl_vertex_buffer(float* vertices, u32 count)
        : _renderer_id(0)
        , _count(count)
    {
        glCreateBuffers(1, &_renderer_id);
        glBindBuffer(GL_ARRAY_BUFFER, _renderer_id);
        glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW);
    }

    opengl_vertex_buffer::~opengl_vertex_buffer()
    {
        glDeleteBuffers(1, &_renderer_id);
    }

    auto opengl_vertex_buffer::bind() const -> void
    {
        glBindBuffer(GL_ARRAY_BUFFER, _renderer_id);
    }

    auto opengl_vertex_buffer::unbind() const -> void
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    auto opengl_vertex_buffer::get_count() const -> u32
    {
        return _count;
    }

    auto opengl_vertex_buffer::set_layout(const buffer_layout& layout) -> void
    {
        _layout = layout;
    }

    auto opengl_vertex_buffer::get_layout() -> buffer_layout&
    {
        return _layout;
    }

    auto opengl_vertex_buffer::set_data(const void* data, u32 size) -> void
    {
        glBindBuffer(GL_ARRAY_BUFFER, _renderer_id);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }
}
