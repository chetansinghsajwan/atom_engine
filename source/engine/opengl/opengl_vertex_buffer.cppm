module;
#include "glad/glad.h"

export module atom.engine:opengl.vertex_buffer;
import atom_core;
import :rendering.vertex_buffer;
import :rendering.buffer_layout;

namespace atom::engine
{
    class opengl_vertex_buffer: public vertex_buffer
    {
    public:
        opengl_vertex_buffer(u32 size)
            : _renderer_id(0)
            , _count(size)
        {
            glCreateBuffers(1, &_renderer_id);
            glBindBuffer(GL_ARRAY_BUFFER, _renderer_id);
            glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
        }

        opengl_vertex_buffer(float* vertices, u32 count)
            : _renderer_id(0)
            , _count(count)
        {
            glCreateBuffers(1, &_renderer_id);
            glBindBuffer(GL_ARRAY_BUFFER, _renderer_id);
            glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW);
        }

        virtual ~opengl_vertex_buffer()
        {
            glDeleteBuffers(1, &_renderer_id);
        }

    public:
        virtual auto bind() const -> void override
        {
            glBindBuffer(GL_ARRAY_BUFFER, _renderer_id);
        }

        virtual auto unbind() const -> void override
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        virtual auto get_count() const -> u32 override
        {
            return _count;
        }

        virtual auto set_layout(const buffer_layout& layout) -> void override
        {
            _layout = layout;
        }

        virtual auto get_layout() -> buffer_layout& override
        {
            return _layout;
        }

        virtual auto set_data(const void* data, u32 size) -> void override
        {
            glBindBuffer(GL_ARRAY_BUFFER, _renderer_id);
            glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
        }

    private:
        u32 _renderer_id;
        u32 _count;
        buffer_layout _layout;
    };
}
