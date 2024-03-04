#pragma once
#include "engine/rendering/graphics_context.h"

#include "GLFW/glfw3.h"

namespace atom::engine
{
    class opengl_context: public graphics_context
    {
    public:
        opengl_context(GLFWwindow* window);

    public:
        virtual auto initialize() -> void override;
        virtual auto swap_buffers() -> void override;

    private:
        GLFWwindow* _window;
    };
}
