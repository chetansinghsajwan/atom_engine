#include "opengl_texture2d.h"
#include "atom/engine/logging.h"
#include "stb_image.h"
#include "glad/glad.h"

namespace atom::engine
{
    opengl_texture2d::opengl_texture2d(u32 width, u32 height)
        : _file_path()
        , _width(width)
        , _height(height)
        , _renderer_id(0)
        , _gl_format(GL_RGBA8)
        , _gl_data_format(GL_RGBA)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &_renderer_id);
        glTextureStorage2D(_renderer_id, 1, _gl_format, _width, _height);
        glTextureParameteri(_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(_renderer_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(_renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(_renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    opengl_texture2d::opengl_texture2d(string_view file_path)
        : _file_path(file_path)
        , _width(0)
        , _height(0)
        , _renderer_id(0)
        , _gl_format(0)
        , _gl_data_format(0)
    {
        ATOM_ENGINE_LOG_INFO("loading texture '{}'", file_path);

        int x, y, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(file_path.get_data(), &x, &y, &channels, 0);
        if (data == nullptr)
        {
            ATOM_ENGINE_LOG_ERROR("loading texture failed.");
            return;
        }

        _height = y;
        _width = x;

        if (channels == 3)
        {
            _gl_format = GL_RGB8;
            _gl_data_format = GL_RGB;
        }
        else if (channels == 4)
        {
            _gl_format = GL_RGBA8;
            _gl_data_format = GL_RGBA;
        }
        else
        {
            ATOM_PANIC(
                "atom.engine only supports rgb and rgba texture formats for now. channels: {}",
                channels);
        }

        glCreateTextures(GL_TEXTURE_2D, 1, &_renderer_id);
        glTextureStorage2D(_renderer_id, 1, _gl_format, _width, _height);
        glTextureParameteri(_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(_renderer_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(_renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(_renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTextureSubImage2D(
            _renderer_id, 0, 0, 0, _width, _height, _gl_data_format, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
        ATOM_ENGINE_LOG_INFO("loading texture completed.");
    }

    opengl_texture2d::~opengl_texture2d()
    {
        glDeleteTextures(1, &_renderer_id);
    }

    auto opengl_texture2d::bind(u32 slot) -> void
    {
        glBindTextureUnit(slot, _renderer_id);
    }

    auto opengl_texture2d::set_data(const void* data, u32 size) -> void
    {
        u32 bytes_per_pixel = _gl_data_format == GL_RGBA ? 4 : 3;
        ATOM_DEBUG_EXPECTS(size == _width * _height * bytes_per_pixel, "data must be entire texture.");

        glTextureSubImage2D(
            _renderer_id, 0, 0, 0, _width, _height, _gl_data_format, GL_UNSIGNED_BYTE, data);
    }
}
