#include "opengl_context.h"
#include "atom.core.h"

#include "glad/glad.h"

namespace atom::engine
{
    opengl_context::opengl_context(GLFWwindow* window)
        : _window(window)
    {}

    auto opengl_context::initialize() -> void
    {
        glfwMakeContextCurrent(_window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        contracts::asserts(status != 0, "failed to initialize glad.");
    }

    auto opengl_context::swap_buffers() -> void
    {
        glfwSwapBuffers(_window);
    }
}
