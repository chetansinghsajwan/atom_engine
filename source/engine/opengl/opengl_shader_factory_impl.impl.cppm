module;
#include "glad/glad.h"

module atom.engine:opengl.shader_factory_impl.impl;

import atom.core;
import atom.logging;
import :opengl.shader_factory_impl;

namespace atom::engine
{
    opengl_shader_factory_impl::opengl_shader_factory_impl()
    {
        auto logger_result = logging::logger_manager::create_logger({
            .name = "opengl_shader_factory",
        });

        _logger = logger_result.get_value_checked();

        // glslang::InitializeProcess();
    }

    opengl_shader_factory_impl::~opengl_shader_factory_impl()
    {
        // glslang::FinalizeProcess();

        delete _logger;
    }

    enum class shader_stage
    {
        vertex_shader,
        fragement_shader,
        compute_shader,
    };

    struct shader_compilation_context
    {
        string_view vertex_shader;
        string_view fragement_shader;
        string_view compute_shader;
    };

    auto opengl_shader_factory_impl::_compile(string_view source, int shader_type) -> bool
    {
        return true;
    }

    auto opengl_shader_factory_impl::_create_from_source(
        string_view vertex_source, string_view fragment_source) -> shader*
    {
        // _compile(vertex_source, EShLangVertex);
        // _compile(fragment_source, EShLangFragment);

        GLuint program = 0;
        return new opengl_shader(program);
    }

    auto opengl_shader_factory_impl::_destroy(shader* shader) -> void
    {
        opengl_shader* gl_shader = reinterpret_cast<opengl_shader*>(shader);
        glDeleteProgram(gl_shader->get_program_id());
    }
}
