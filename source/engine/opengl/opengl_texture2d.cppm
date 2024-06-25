module;
#include "glad/glad.h"
#include "stb/stb_image.h"

export module atom.engine:opengl.texture2d;

import :rendering;
import atom.core;
import :logging;

namespace atom::engine
{
    class opengl_texture2d: public texture2d
    {
    public:
        opengl_texture2d(GLuint renderer_id, texture_format format, u32 width, u32 height)
            : texture2d{ format }
            , _gl_renderer_id{ renderer_id }
            , _width{ width }
            , _height{ height }
        {}

        virtual ~opengl_texture2d()
        {
            glDeleteTextures(1, &_gl_renderer_id);
        }

    public:
        virtual auto get_renderer_id() const -> u32 override final
        {
            return _gl_renderer_id;
        }

        virtual auto get_height() const -> u32 override final
        {
            return _height;
        }

        virtual auto get_width() const -> u32 override final
        {
            return _width;
        }

        virtual auto bind(u32 slot = 0) -> void override
        {
            glBindTextureUnit(slot, _gl_renderer_id);
        }

    private:
        GLuint _gl_renderer_id;
        u32 _height;
        u32 _width;
    };
}
