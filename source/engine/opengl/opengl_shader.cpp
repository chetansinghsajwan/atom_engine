import atom.core;
import atom.logging;

#include "opengl_shader.h"
#include "atom/engine/logging.h"
#include "glad/glad.h"

namespace atom::engine
{
    opengl_shader::opengl_shader(GLuint program)
        : _program(program)
    {}

    opengl_shader::~opengl_shader() {}

    auto opengl_shader::bind() -> void
    {
        glUseProgram(_program);
    }

    auto opengl_shader::unbind() -> void
    {
        glUseProgram(0);
    }

    auto opengl_shader::get_program_id() -> GLuint
    {
        return _program;
    }

    auto opengl_shader::set_uniform_int(string_view name, i32 value) -> void
    {
        upload_uniform_int(name, value);
    }

    auto opengl_shader::set_uniform_float(string_view name, float value) -> void
    {
        upload_uniform_float(name, value);
    }

    auto opengl_shader::set_uniform_float4(string_view name, const vec4& vec) -> void
    {
        upload_uniform_float4(name, vec);
    }

    auto opengl_shader::set_uniform_mat4(string_view name, const mat4& mat) -> void
    {
        upload_uniform_mat4(name, mat);
    }

    auto opengl_shader::set_int_array(string_view name, const int* array, usize count) -> void
    {
        upload_uniform_int_array(name, array, count);
    }

    auto opengl_shader::upload_uniform_int(string_view name, const GLint value) -> void
    {
        GLint location = glGetUniformLocation(_program, name.get_data());
        ATOM_DEBUG_EXPECTS(location != -1, name.to_std());

        glUniform1i(location, value);
    }

    auto opengl_shader::upload_uniform_float(string_view name, float value) -> void
    {
        GLint location = glGetUniformLocation(_program, name.get_data());
        ATOM_DEBUG_EXPECTS(location != -1);

        glUniform1f(location, value);
    }

    auto opengl_shader::upload_uniform_float4(string_view name, const glm::vec4& vec) -> void
    {
        GLint location = glGetUniformLocation(_program, name.get_data());
        ATOM_DEBUG_EXPECTS(location != -1);

        glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
    }

    auto opengl_shader::upload_uniform_mat4(string_view name, const glm::mat4& mat) -> void
    {
        GLint location = glGetUniformLocation(_program, name.get_data());
        ATOM_DEBUG_EXPECTS(location != -1);

        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
    }

    auto opengl_shader::upload_uniform_int_array(string_view name, const int* array, usize count) -> void
    {
        GLint location = glGetUniformLocation(_program, name.get_data());
        ATOM_DEBUG_EXPECTS(location != -1);

		glUniform1iv(location, count, array);
    }
}
