#pragma once
#include "atom/engine/rendering/shader.h"
#include "atom/engine/math.h"
#include "glad/glad.h"

namespace atom::engine
{
    class opengl_shader: public shader
    {
    public:
        opengl_shader(GLuint program);
        virtual ~opengl_shader();

    public:
        virtual auto bind() -> void override;
        virtual auto unbind() -> void override;

        virtual auto set_uniform_int(string_view name, i32 value) -> void override;
        virtual auto set_uniform_float4(string_view name, const vec4& vec) -> void override;
        virtual auto set_uniform_mat4(string_view name, const mat4& mat) -> void override;

        auto get_program_id() -> GLuint;
        auto upload_uniform_int(string_view name, GLint value) -> void;
        auto upload_uniform_float4(string_view name, const glm::vec4& vec) -> void;
        auto upload_uniform_mat4(string_view name, const glm::mat4& mat) -> void;

    private:
        GLuint _program;
    };
}
