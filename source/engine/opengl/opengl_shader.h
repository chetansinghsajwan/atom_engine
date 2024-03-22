#pragma once
#include "atom/engine/rendering/shader.h"
#include "glad/glad.h"

namespace atom::engine
{
    class opengl_shader: public shader
    {
    public:
        opengl_shader(string_view vertex_source, string_view fragement_source);
        virtual ~opengl_shader();

    public:
        virtual auto bind() -> void override;
        virtual auto unbind() -> void override;
        virtual auto upload_uniform_mat4(string_view name, const glm::mat4& mat) -> void override;

    private:
        GLuint _program;
    };
}
