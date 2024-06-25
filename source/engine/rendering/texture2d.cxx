module atom.engine:rendering.texture2d.impl;

import atom.core;
import :math;
import :rendering.texture;
import :rendering.texture2d;

namespace atom::engine
{
    texture2d::texture2d(texture_format format, u32vec2 size)
        : texture{ format, size }
    {}

    texture2d::~texture2d() {}
}
