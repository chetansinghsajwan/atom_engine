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
        opengl_texture2d(u32 width, u32 height)
            : _file_path{}
            , _width{ width }
            , _height{ height }
            , _renderer_id{ 0 }
            , _gl_format{ GL_RGBA8 }
            , _gl_data_format{ GL_RGBA }
        {
            glCreateTextures(GL_TEXTURE_2D, 1, &_renderer_id);
            glTextureStorage2D(_renderer_id, 1, _gl_format, _width, _height);
            glTextureParameteri(_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTextureParameteri(_renderer_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTextureParameteri(_renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteri(_renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }

        opengl_texture2d(string_view file_path)
            : _file_path(file_path)
            , _width(0)
            , _height(0)
            , _renderer_id(0)
            , _gl_format(0)
            , _gl_data_format(0)
        {
            ATOM_ENGINE_LOG_INFO("loading texture '{}'", file_path);

            int x;
            int y;
            int channels;
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
                contract_panic(
                    "atom.engine only supports rgb and rgba texture formats for now. channels: {}");
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

        virtual ~opengl_texture2d()
        {
            glDeleteTextures(1, &_renderer_id);
        }

    public:
        virtual auto get_renderer_id() const -> u32 override final
        {
            return _renderer_id;
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
            glBindTextureUnit(slot, _renderer_id);
        }

        virtual auto set_data(const void* data, u32 size) -> void override
        {
            u32 bytes_per_pixel = _gl_data_format == GL_RGBA ? 4 : 3;
            contract_debug_expects(
                size == _width * _height * bytes_per_pixel, "data must be entire texture.");

            glTextureSubImage2D(
                _renderer_id, 0, 0, 0, _width, _height, _gl_data_format, GL_UNSIGNED_BYTE, data);
        }

    private:
        string _file_path;
        u32 _renderer_id;
        u32 _height;
        u32 _width;
        GLenum _gl_format;
        GLenum _gl_data_format;
    };
}
