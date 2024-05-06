#pragma once
#include "engine/rendering/frame_buffer.h"

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

        virtual auto get_specs() const -> const frame_buffer_specs& override
        {
            return _specs;
        }

        virtual auto get_color_attachment() const -> u32 override
        {
            return _color_attachment;
        }

    private:
        auto _invalidate() -> void;

    private:
        uint32_t _renderer_id;
        uint32_t _color_attachment;
        uint32_t _depth_attatchment;
        frame_buffer_specs _specs;
    };
}
