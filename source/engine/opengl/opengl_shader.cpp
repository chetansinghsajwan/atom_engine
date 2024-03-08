#include "opengl_shader.h"
#include "atom/engine/logging.h"
#include "glad/glad.h"

namespace atom::engine
{
    opengl_shader::opengl_shader(string_view vertex_source, string_view fragment_source)
        : _program(0)
    {
        // Create an empty vertex shader handle
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        // Send the vertex shader source code to GL
        const GLchar* source = (const GLchar*)vertex_source.get_data();
        glShaderSource(vertexShader, 1, &source, 0);

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

            ATOM_ENGINE_LOG_PANIC("vertex shader compilation failed. infoLog: {}", infoLog);
            return;
        }

        ATOM_ENGINE_LOG_INFO("vertex shader compiled.");
        ATOM_ENGINE_LOG_INFO("compiling fragment shader...");

        // Create an empty fragment shader handle
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        // Send the fragment shader source code to GL
        source = (const GLchar*)fragment_source.get_data();
        glShaderSource(fragmentShader, 1, &source, 0);

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

            ATOM_ENGINE_LOG_PANIC("fragment shader compilation failed. infoLog: {}", infoLog);
            return;
        }

        ATOM_ENGINE_LOG_INFO("fragment shader compiled.");

        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a program.
        // Get a program object.
        GLuint _program = glCreateProgram();

        // Attach our shaders to our program
        glAttachShader(_program, vertexShader);
        glAttachShader(_program, fragmentShader);

        ATOM_ENGINE_LOG_INFO("linking program...");

        // Link our program
        glLinkProgram(_program);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(_program, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(_program, maxLength, &maxLength, &infoLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(_program);
            // Don't leak shaders either.
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            ATOM_ENGINE_LOG_PANIC("program linking failed. infoLog: {}", infoLog);
            return;
        }

        ATOM_ENGINE_LOG_INFO("program linked.");

        // Always detach shaders after a successful link.
        glDetachShader(_program, vertexShader);
        glDetachShader(_program, fragmentShader);
    }

    opengl_shader::~opengl_shader()
    {
        glDeleteProgram(_program);
    }

    auto opengl_shader::bind() -> void
    {
        glUseProgram(_program);
    }

    auto opengl_shader::unbind() -> void
    {
        glUseProgram(0);
    }
}
