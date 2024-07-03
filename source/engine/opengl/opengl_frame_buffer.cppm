module;
#include "glad/glad.h"

export module atom_engine:opengl.frame_buffer;

import atom_core;
import :math;
import :rendering.frame_buffer;

namespace atom::engine
{
    class opengl_frame_buffer: public frame_buffer
    {
    public:
        opengl_frame_buffer(const frame_buffer_specs& specs)
            : _specs(specs)
        {
            _invalidate();
        }

        virtual ~opengl_frame_buffer()
        {
            glDeleteFramebuffers(1, &_renderer_id);
            glDeleteTextures(1, &_color_attachment);
            glDeleteTextures(1, &_depth_attatchment);
        }

    public:
        virtual auto bind() -> void override
        {
            glBindFramebuffer(GL_FRAMEBUFFER, _renderer_id);
            glViewport(0, 0, _specs.width, _specs.height);
        }

        virtual auto unbind() -> void override
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        virtual auto resize(f32vec2 size) -> void override
        {
            _specs.width = size.x;
            _specs.height = size.y;

            _invalidate();
        }

        virtual auto get_specs() const -> const frame_buffer_specs& override
        {
            return _specs;
        }

        virtual auto get_color_attachment_renderer_id() const -> u32 override
        {
            return _color_attachment;
        }

    private:
        auto _invalidate() -> void
        {
            if (_renderer_id != 0)
            {
                glDeleteFramebuffers(1, &_renderer_id);
                glDeleteTextures(1, &_color_attachment);
                glDeleteTextures(1, &_depth_attatchment);
            }

            glCreateFramebuffers(1, &_renderer_id);
            glBindFramebuffer(GL_FRAMEBUFFER, _renderer_id);

            glCreateTextures(GL_TEXTURE_2D, 1, &_color_attachment);
            glBindTexture(GL_TEXTURE_2D, _color_attachment);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _specs.width, _specs.height, 0, GL_RGBA,
                GL_UNSIGNED_BYTE, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glFramebufferTexture2D(
                GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _color_attachment, 0);

            glCreateTextures(GL_TEXTURE_2D, 1, &_depth_attatchment);
            glBindTexture(GL_TEXTURE_2D, _depth_attatchment);
            glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, _specs.width, _specs.height);
            glFramebufferTexture2D(
                GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _depth_attatchment, 0);

            contract_debug_asserts(
                glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
                "opengl_frame_buffer is incomplete.");

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

    private:
        uint32_t _renderer_id = 0;
        uint32_t _color_attachment = 0;
        uint32_t _depth_attatchment = 0;
        frame_buffer_specs _specs;
    };
}
