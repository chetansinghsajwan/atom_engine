#include "engine/opengl/opengl_frame_buffer.h"
#include "glad/glad.h"

namespace atom::engine
{
    opengl_frame_buffer::opengl_frame_buffer(const frame_buffer_specs& specs)
        : _specs(specs)
    {
        _invalidate();
    }

    opengl_frame_buffer::~opengl_frame_buffer()
    {
        glDeleteFramebuffers(1, &_renderer_id);
        glDeleteTextures(1, &_color_attachment);
        glDeleteTextures(1, &_depth_attatchment);
    }

    auto opengl_frame_buffer::bind() -> void
    {
        glBindFramebuffer(GL_FRAMEBUFFER, _renderer_id);
        glViewport(0, 0, _specs.width, _specs.height);
    }

    auto opengl_frame_buffer::unbind() -> void
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    auto opengl_frame_buffer::resize(vec2 size) -> void
    {
        _specs.width = size.x;
        _specs.height = size.y;

        _invalidate();
    }

    auto opengl_frame_buffer::_invalidate() -> void
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

        ATOM_DEBUG_ASSERTS(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
            "opengl_frame_buffer is incomplete.");

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}
