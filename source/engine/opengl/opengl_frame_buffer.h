#pragma once
#include "engine/rendering/frame_buffer.h"
#include "atom/engine/math.h"

namespace atom::engine
{
    class opengl_frame_buffer: public frame_buffer
    {
    public:
        opengl_frame_buffer(const frame_buffer_specs& specs);
        virtual ~opengl_frame_buffer(); 

    public:
        virtual auto bind() -> void override;
        virtual auto unbind() -> void override;
        virtual auto resize(vec2 size) -> void override;

        virtual auto get_specs() const -> const frame_buffer_specs& override
        {
            return _specs;
        }

        virtual auto get_color_attachment_renderer_id() const -> u32 override
        {
            return _color_attachment;
        }

    private:
        auto _invalidate() -> void;

    private:
        uint32_t _renderer_id = 0;
        uint32_t _color_attachment = 0;
        uint32_t _depth_attatchment = 0;
        frame_buffer_specs _specs;
    };
}
