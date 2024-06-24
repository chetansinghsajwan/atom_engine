module;
#include "glad/glad.h"

export module atom.engine:opengl.index_buffer;

import atom.core;
import :rendering;

namespace atom::engine
{
    class opengl_index_buffer: public index_buffer
    {
    public:
        opengl_index_buffer(u32* indices, u32 count)
            : _renderer_id{ 0 }
            , _count{ count }
        {
            glCreateBuffers(1, &_renderer_id);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _renderer_id);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), indices, GL_STATIC_DRAW);
        }

        virtual ~opengl_index_buffer()
        {
            glDeleteBuffers(1, &_renderer_id);
        }

    public:
        virtual auto bind() const -> void override
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _renderer_id);
        }

        virtual auto unbind() const -> void override
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        virtual auto get_count() const -> u32 override
        {
            return _count;
        }

    private:
        u32 _renderer_id;
        u32 _count;
    };
}
