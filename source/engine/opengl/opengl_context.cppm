module;
#include "GLFW/glfw3.h"
#include "glad/glad.h"

export module atom_engine:opengl.context;

import atom_core;
import :rendering;

namespace atom::engine
{
    class opengl_context: public graphics_context
    {
    public:
        opengl_context(GLFWwindow* window)
            : _window(window)
        {}

    public:
        virtual auto initialize() -> void override
        {
            glfwMakeContextCurrent(_window);
            int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            contract_asserts(status != 0, "failed to initialize glad.");
        }

        virtual auto finalize() -> void override {}

        virtual auto swap_buffers() -> void override
        {
            glfwSwapBuffers(_window);
        }

    private:
        GLFWwindow* _window;
    };
}
