module;
#include "glad/glad.h"

module atom.engine:opengl.shader_factory_impl.impl;

import atom.core;
import atom.logging;
import :opengl.shader_factory_impl;
import :shaders.shader_compiler;

namespace atom::engine
{
    opengl_shader_factory_impl::opengl_shader_factory_impl()
    {
        auto logger_result = logging::logger_manager::create_logger({
            .name = "opengl_shader_factory",
        });

        _logger = logger_result.get_value_checked();
    }

    opengl_shader_factory_impl::~opengl_shader_factory_impl()
    {
        delete _logger;
    }

    auto opengl_shader_factory_impl::_compile(string_view source, int shader_type) -> bool
    {
        return true;
    }

    auto opengl_shader_factory_impl::_create_from_source(
        string_view vertex_source, string_view fragment_source) -> shader*
    {
        GLuint program = 0;
        return new opengl_shader(program);
    }

    auto opengl_shader_factory_impl::_destroy(shader* shader) -> void
    {
        opengl_shader* gl_shader = reinterpret_cast<opengl_shader*>(shader);
        glDeleteProgram(gl_shader->get_program_id());
    }
}
