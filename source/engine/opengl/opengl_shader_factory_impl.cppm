module;
#include "glad/glad.h"

export module atom.engine:opengl.shader_factory_impl;

import atom.core;
import atom.logging;
import :rendering;
import :opengl.shader;

namespace atom::engine
{
    class opengl_shader_factory_impl: public shader_factory_impl
    {
    public:
        opengl_shader_factory_impl()
        {
            _logger = logging::logger_manager::create_logger({ .name = "opengl_shader_factory" })
                          .get_value();
        }

        virtual ~opengl_shader_factory_impl()
        {
            delete _logger;
        }

    public:
        virtual auto create(
            string_view vertex_source, string_view fragment_source) -> shader* override
        {
            // Create an empty vertex shader handle
            GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);

            // Send the vertex shader source code to GL
            const GLchar* vertex_shader_source = (const GLchar*)vertex_source.get_data();
            GLint vertex_shader_source_length = vertex_source.get_count();
            glShaderSource(vertex_shader, 1, &vertex_shader_source, &vertex_shader_source_length);

            _logger->log_info("compiling vertex shader...");

            // Compile the vertex shader
            glCompileShader(vertex_shader);

            GLint is_compiled = 0;
            glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &is_compiled);
            if (is_compiled == GL_FALSE)
            {
                GLint max_length = 0;
                glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &max_length);

                // The max_length includes the NULL character
                std::vector<GLchar> info_log(max_length);
                glGetShaderInfoLog(vertex_shader, max_length, &max_length, &info_log[0]);

                // We don't need the shader anymore.
                glDeleteShader(vertex_shader);

                _logger->log_fatal(
                    "compilation failed for vertex shader. info_log: {}", info_log.data());

                contract_panic();
            }

            _logger->log_info("compiled vertex shader.");
            _logger->log_info("compiling fragment shader...");

            // Create an empty fragment shader handle
            GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

            // Send the fragment shader source code to GL
            const GLchar* fragement_shader_source = (const GLchar*)fragment_source.get_data();
            GLint fragement_shader_source_length = vertex_source.get_count() - 1;
            glShaderSource(
                fragment_shader, 1, &fragement_shader_source, &fragement_shader_source_length);

            // Compile the fragment shader
            glCompileShader(fragment_shader);

            glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &is_compiled);
            if (is_compiled == GL_FALSE)
            {
                GLint max_length = 0;
                glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &max_length);

                // The max_length includes the NULL character
                std::vector<GLchar> info_log(max_length);
                glGetShaderInfoLog(fragment_shader, max_length, &max_length, &info_log[0]);

                // We don't need the shader anymore.
                // Either of them. Don't leak shaders.
                glDeleteShader(fragment_shader);
                glDeleteShader(vertex_shader);

                _logger->log_fatal(
                    "compilation failed for fragment shader. info_log: {}", info_log.data());

                contract_panic();
            }

            _logger->log_info("compiled fragment shader.");

            // Vertex and fragment shaders are successfully compiled.
            // Now time to link them together into a program.
            // Get a program object.
            GLuint program = glCreateProgram();

            // Attach our shaders to our program
            glAttachShader(program, vertex_shader);
            glAttachShader(program, fragment_shader);

            _logger->log_info("linking program...");

            // Link our program
            glLinkProgram(program);

            // Note the different functions here: glGetProgram* instead of glGetShader*.
            GLint isLinked = 0;
            glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
            if (isLinked == GL_FALSE)
            {
                GLint max_length = 0;
                glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_length);

                // The max_length includes the NULL character
                std::vector<GLchar> info_log(max_length);
                glGetProgramInfoLog(program, max_length, &max_length, &info_log[0]);

                // We don't need the program anymore.
                glDeleteProgram(program);

                // Don't leak shaders either.
                glDeleteShader(vertex_shader);
                glDeleteShader(fragment_shader);

                _logger->log_fatal("linking failed for program. info_log: {}", info_log.data());
                contract_panic();
            }

            _logger->log_info("linked program.");

            // Always detach shaders after a successful link.
            glDetachShader(program, vertex_shader);
            glDetachShader(program, fragment_shader);

            return new opengl_shader(program);
        }

        virtual auto destroy(shader* shader) -> void override
        {
            opengl_shader* gl_shader = reinterpret_cast<opengl_shader*>(shader);
            glDeleteProgram(gl_shader->get_program_id());
        }

    private:
        logging::logger* _logger = nullptr;
    };
}
