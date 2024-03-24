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

    auto opengl_shader::upload_uniform_int(string_view name, const GLint value) -> void
    {
        GLint location = glGetUniformLocation(_program, name.get_data());
        ATOM_DEBUG_EXPECTS(location != -1);

        glUniform1i(location, value);
    }

    auto opengl_shader::upload_uniform_mat4(string_view name, const glm::mat4& mat) -> void
    {
        GLint location = glGetUniformLocation(_program, name.get_data());
        ATOM_DEBUG_EXPECTS(location != -1);

        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
    }
}
