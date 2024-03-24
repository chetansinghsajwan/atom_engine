#include "engine/opengl/opengl_shader_factory_impl.h"
#include "atom/engine/logging.h"

namespace atom::engine
{
    auto opengl_shader_factory_impl::create(string_view vertex_source, string_view fragment_source)
        -> opengl_shader*
    {
        // Create an empty vertex shader handle
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        // Send the vertex shader source code to GL
        const GLchar* source = (const GLchar*)vertex_source.get_data();
        GLint source_length = vertex_source.get_count();
        glShaderSource(vertexShader, 1, &source, &source_length);

        ATOM_ENGINE_LOG_INFO("compiling vertex shader...");

        // Compile the vertex shader
        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            glDeleteShader(vertexShader);

            ATOM_ENGINE_LOG_PANIC(
                "compilation failed for vertex shader. infoLog: {}", infoLog.data());

            return nullptr;
        }

        ATOM_ENGINE_LOG_INFO("compiled vertex shader.");
        ATOM_ENGINE_LOG_INFO("compiling fragment shader...");

        // Create an empty fragment shader handle
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        // Send the fragment shader source code to GL
        source = (const GLchar*)fragment_source.get_data();
        source_length = vertex_source.get_count();
        glShaderSource(fragmentShader, 1, &source, &source_length);

        // Compile the fragment shader
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            // Either of them. Don't leak shaders.
            glDeleteShader(fragmentShader);
            glDeleteShader(vertexShader);

            ATOM_ENGINE_LOG_PANIC(
                "compilation failed for fragment shader. infoLog: {}", infoLog.data());
            return nullptr;
        }

        ATOM_ENGINE_LOG_INFO("compiled fragment shader.");

        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a program.
        // Get a program object.
        GLuint program = glCreateProgram();

        // Attach our shaders to our program
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        ATOM_ENGINE_LOG_INFO("linking program...");

        // Link our program
        glLinkProgram(program);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(program);
            // Don't leak shaders either.
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            ATOM_ENGINE_LOG_PANIC("linking failed for program. infoLog: {}", infoLog.data());
            return nullptr;
        }

        ATOM_ENGINE_LOG_INFO("linked program.");

        // Always detach shaders after a successful link.
        glDetachShader(program, vertexShader);
        glDetachShader(program, fragmentShader);

        return new opengl_shader(program);
    }

    auto opengl_shader_factory_impl::destroy(class shader* shader) -> void
    {
        opengl_shader* gl_shader = reinterpret_cast<opengl_shader*>(shader);
        glDeleteProgram(gl_shader->get_program_id());
    }
}
