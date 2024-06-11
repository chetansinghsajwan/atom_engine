module;
#include "glad/glad.h"

export module atom.engine:opengl.shader;

import atom.core;
import :math;
import :rendering.shader;

namespace atom::engine
{
    class opengl_shader: public shader
    {
    public:
        opengl_shader(GLuint program)
            : _program{ program }
        {}

        virtual ~opengl_shader() {}

    public:
        virtual auto bind() -> void override
        {
            glUseProgram(_program);
        }

        virtual auto unbind() -> void override
        {
            glUseProgram(0);
        }

        virtual auto set_uniform_int(string_view name, i32 value) -> void override
        {
            upload_uniform_int(name, value);
        }

        virtual auto set_uniform_float(string_view name, float value) -> void override
        {
            upload_uniform_float(name, value);
        }

        virtual auto set_uniform_float4(string_view name, const f32vec4& value) -> void override
        {
            upload_uniform_float4(name, value);
        }

        virtual auto set_uniform_mat4(string_view name, const f32mat4& value) -> void override
        {
            upload_uniform_mat4(name, value);
        }

        virtual auto set_int_array(string_view name, const int* array, usize count) -> void override
        {
            upload_uniform_int_array(name, array, count);
        }

        auto get_program_id() -> GLuint
        {
            return _program;
        }

        auto upload_uniform_int(string_view name, GLint value) -> void
        {
            GLint location = get_uniform_location(name);
            contract_debug_expects(location != -1, name.to_std());

            glUniform1i(location, value);
        }

        auto upload_uniform_float(string_view name, float value) -> void
        {
            GLint location = get_uniform_location(name);
            contract_debug_expects(location != -1);

            glUniform1f(location, value);
        }

        auto upload_uniform_float4(string_view name, const f32vec4& vec) -> void
        {
            GLint location = get_uniform_location(name);
            contract_debug_expects(location != -1);

            glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
        }

        auto upload_uniform_mat4(string_view name, const f32mat4& mat) -> void
        {
            GLint location = get_uniform_location(name);
            contract_debug_expects(location != -1);

            glUniformMatrix4fv(location, 1, GL_FALSE, math::value_ptr(mat));
        }

        auto upload_uniform_int_array(string_view name, const int* array, usize count) -> void
        {
            GLint location = get_uniform_location(name);
            contract_debug_expects(location != -1);

            glUniform1iv(location, count, array);
        }

        auto get_uniform_location(string_view name) -> GLint
        {
            return glGetUniformLocation(_program, name.get_data());
        }

    private:
        GLuint _program;
        string _name;
    };
}
