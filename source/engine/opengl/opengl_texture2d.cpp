#include "opengl_texture2d.h"
#include "atom/engine/logging.h"
#include "stb_image.h"
#include "glad/glad.h"

namespace atom::engine
{
    opengl_texture2d::opengl_texture2d(string_view file_path)
        : _file_path(file_path)
        , _height(0)
        , _width(0)
        , _renderer_id(0)
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

        int gl_format = 0;
        int gl_data_format = 0;

        if (channels == 3)
        {
            gl_format = GL_RGB8;
            gl_data_format = GL_RGB;
        }
        else if (channels == 4)
        {
            gl_format = GL_RGBA8;
            gl_data_format = GL_RGBA;
        }
        else
        {
            ATOM_PANIC(
                "atom.engine only supports rgb and rgba texture formats for now. channels: {}",
                channels);
        }

        glCreateTextures(GL_TEXTURE_2D, 1, &_renderer_id);
        glTextureStorage2D(_renderer_id, 1, gl_format, _width, _height);
        glTextureParameteri(_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(_renderer_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureSubImage2D(
            _renderer_id, 0, 0, 0, _width, _height, gl_data_format, GL_UNSIGNED_BYTE, data);

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
}
