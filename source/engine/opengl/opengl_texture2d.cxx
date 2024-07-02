module;
#include "glad/glad.h"

module atom.engine:opengl.texture2d.impl;

import atom_core;
import :math;
import :rendering;
import :opengl.texture2d;

namespace atom::engine
{
    opengl_texture2d::opengl_texture2d(GLuint renderer_id, texture_format format, u32vec2 size)
        : texture2d{ format, size }
        , _gl_renderer_id{ renderer_id }
    {}

    opengl_texture2d::~opengl_texture2d()
    {
        glDeleteTextures(1, &_gl_renderer_id);
    }

    auto opengl_texture2d::get_renderer_id() const -> GLuint
    {
        return _gl_renderer_id;
    }
}
