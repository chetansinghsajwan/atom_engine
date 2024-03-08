#pragma once
#include "engine/rendering/index_buffer.h"

namespace atom::engine
{
    class opengl_index_buffer: public index_buffer
    {
    public:
        opengl_index_buffer(uint32_t* indices, u32 count);
        virtual ~opengl_index_buffer();

    public:
        virtual auto bind() const -> void override;
        virtual auto unbind() const -> void override;
        virtual auto get_count() const -> u32 override;

    private:
        uint32_t _renderer_id;
        u32 _count;
    };
}
