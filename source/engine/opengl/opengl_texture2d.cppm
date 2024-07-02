module;
#include "glad/glad.h"

export module atom.engine:opengl.texture2d;

import atom_core;
import :math;
import :rendering;

namespace atom::engine
{
    class opengl_texture2d: public texture2d
    {
    public:
        opengl_texture2d(GLuint renderer_id, texture_format format, u32vec2 size);

        virtual ~opengl_texture2d();

    public:
        auto get_renderer_id() const -> u32;

    private:
        GLuint _gl_renderer_id;
    };
}
