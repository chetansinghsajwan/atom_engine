module;
#include "glad/glad.h"
#include "stb/stb_image.h"

module atom.engine:rendering.texture_factory.impl;

import atom.core;
import :rendering.texture_factory;
import :rendering.texture2d;
import :opengl;
import :math;

namespace atom::engine
{
    auto texture_factory::create_from_file(string_view file_path)
        -> result<texture2d*, filesystem::filesystem_error, filesystem::noentry_error>
    {
        // _logger->log_info("loading texture '{}'", file_path);

        int x;
        int y;
        int channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(file_path.get_data(), &x, &y, &channels, 0);
        if (data == nullptr)
        {
            // _logger->log_error("loading texture failed.");
            return nullptr;
        }

        u32 height = y;
        u32 width = x;
        GLenum gl_format = 0;
        GLenum gl_data_format = 0;
        GLuint gl_renderer_id = 0;

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
            contract_panic(
                "atom.engine only supports rgb and rgba texture formats for now. channels: {}");
        }

        glCreateTextures(GL_TEXTURE_2D, 1, &gl_renderer_id);
        glTextureStorage2D(gl_renderer_id, 1, gl_format, width, height);
        glTextureParameteri(gl_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(gl_renderer_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(gl_renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(gl_renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTextureSubImage2D(
            gl_renderer_id, 0, 0, 0, width, height, gl_data_format, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
        // _logger->log_info("loading texture completed.");

        return new opengl_texture2d{ gl_renderer_id, width, height };
    }

    auto texture_factory::create_from_data(memory_view data, u32vec2 size) -> texture2d*
    {
        GLuint gl_renderer_id = 0;
        GLenum gl_format{ GL_RGBA8 };
        GLenum gl_data_format{ GL_RGBA };

        glCreateTextures(GL_TEXTURE_2D, 1, &gl_renderer_id);
        glTextureStorage2D(gl_renderer_id, 1, gl_format, size.x, size.y);
        glTextureParameteri(gl_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(gl_renderer_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(gl_renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(gl_renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTextureSubImage2D(gl_renderer_id, 0, 0, 0, size.x, size.y, gl_data_format,
            GL_UNSIGNED_BYTE, data.get_data());

        return new opengl_texture2d{ gl_renderer_id, size.x, size.y };
    }
}
