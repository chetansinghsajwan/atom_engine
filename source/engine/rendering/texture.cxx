module atom_engine:rendering.texture.impl;

import atom_core;
import :math;
import :rendering.texture;

namespace atom::engine
{
    texture::texture(texture_format format, u32vec2 size)
        : _format{ format }
        , _size{ size }
    {}

    texture::~texture() {}

    auto texture::get_format() const -> texture_format
    {
        return _format;
    }

    auto texture::get_size() const -> u32vec2
    {
        return _size;
    }
}
