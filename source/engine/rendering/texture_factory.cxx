module;
#include "glad/glad.h"
#include "stb/stb_image.h"

module atom.engine:rendering.texture_factory.impl;

import atom.core;
import :rendering.texture_factory;
import :rendering.texture;
import :rendering.texture2d;
import :opengl;
import :math;

namespace atom::engine
{
    auto stb_channels_to_atom_texture_format(int stb_channels) -> option<texture_format>
    {
        switch (stb_channels)
        {
            case 3:  return texture_format::rgb8;
            case 4:  return texture_format::rgba8;
            default: return nullopt();
        }
    }

    auto atom_texture_format_to_gl_format(texture_format format) -> pair<GLenum, GLenum>
    {
        switch (format)
        {
            case texture_format::rgb8:  return { GL_RGB, GL_RGB8 };
            case texture_format::rgba8: return { GL_RGBA, GL_RGBA8 };
            default:
            {
                contract_panic("invalid value.");
            }
        }
    }

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

        int stb_x;
        int stb_y;
        int stb_channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* stb_data = stbi_load_from_memory(
            content.get_data(), content.get_size(), &stb_x, &stb_y, &stb_channels, 0);

        if (stb_data == nullptr)
        {
            return runtime_error{ "failed to load image." };
        }

        option<texture_format> format_option = stb_channels_to_atom_texture_format(stb_channels);
        if (not format_option.is_value())
        {
            return runtime_error{ "we only support rgb8 and rgba8 currently." };
        }

        texture_format format = format_option.get();

        pair<GLenum, GLenum> gl_formats = atom_texture_format_to_gl_format(format);
        GLenum gl_format = gl_formats.first;
        GLenum gl_data_format = gl_formats.second;

        GLuint gl_renderer_id = 0;
        u32vec2 texture_size{ stb_x, stb_y };

        glCreateTextures(GL_TEXTURE_2D, 1, &gl_renderer_id);
        glTextureStorage2D(gl_renderer_id, 1, gl_format, texture_size.x, texture_size.y);
        glTextureParameteri(gl_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(gl_renderer_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(gl_renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(gl_renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTextureSubImage2D(
            gl_renderer_id, 0, 0, 0, texture_size.x, texture_size.y, gl_data_format, GL_UNSIGNED_BYTE, stb_data);

        stbi_image_free(stb_data);

        return new opengl_texture2d{ gl_renderer_id, format, texture_size };
    }

    auto texture_factory::create_from_data(
        memory_view data, texture_format format, u32vec2 size) -> texture2d*
    {
        GLuint gl_renderer_id = 0;

        pair<GLenum, GLenum> gl_formats = atom_texture_format_to_gl_format(format);
        GLenum gl_format = gl_formats.first;
        GLenum gl_data_format = gl_formats.second;

        glCreateTextures(GL_TEXTURE_2D, 1, &gl_renderer_id);
        glTextureStorage2D(gl_renderer_id, 1, gl_format, size.x, size.y);
        glTextureParameteri(gl_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(gl_renderer_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(gl_renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(gl_renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTextureSubImage2D(gl_renderer_id, 0, 0, 0, size.x, size.y, gl_data_format,
            GL_UNSIGNED_BYTE, data.get_data());

        return new opengl_texture2d{ gl_renderer_id, format, size };
    }
}
