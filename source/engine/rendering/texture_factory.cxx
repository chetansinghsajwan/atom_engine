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
    auto texture_factory::create_from_file(
        string_view file_path) -> result<texture2d*, runtime_error, filesystem::filesystem_error,
                                   filesystem::noentry_error>
    {
        auto content_result = filesystem::read_file_bytes(file_path);
        if (content_result.is_error())
        {
            return { create_from_result, move(content_result) };
        }

        dynamic_buffer content = move(content_result).get_value();

        int x;
        int y;
        int channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* stb_data =
            stbi_load_from_memory(content.get_data(), content.get_size(), &x, &y, &channels, 0);

        if (stb_data == nullptr)
        {
            return runtime_error{ "failed to load image." };
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
            return runtime_error{ "we only support rgb8 and rgba currently." };
        }

        glCreateTextures(GL_TEXTURE_2D, 1, &gl_renderer_id);
        glTextureStorage2D(gl_renderer_id, 1, gl_format, width, height);
        glTextureParameteri(gl_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(gl_renderer_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(gl_renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(gl_renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTextureSubImage2D(
            gl_renderer_id, 0, 0, 0, width, height, gl_data_format, GL_UNSIGNED_BYTE, stb_data);

        stbi_image_free(stb_data);

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
