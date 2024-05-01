#include "opengl_renderer_api.h"
#include "atom/engine/logging.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace atom::engine
{
    auto opengl_renderer_api::initialize() -> void
    {
        ATOM_ENGINE_LOG_INFO("initializing opengl_renderer...");

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        ATOM_ENGINE_LOG_INFO("initializing opengl_renderer done.");
    }

    auto opengl_renderer_api::finalize() -> void
    {
        ATOM_ENGINE_LOG_INFO("finalizing opengl_renderer...");
        ATOM_ENGINE_LOG_INFO("finalizing opengl_renderer done.");
    }

    auto opengl_renderer_api::set_clear_color(vec4 color) -> void
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    auto opengl_renderer_api::clear_color() -> void
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    auto opengl_renderer_api::draw_indexed(vertex_array* arr) -> void
    {
        glDrawElements(
            GL_TRIANGLES, arr->get_index_buffer()->get_count(), GL_UNSIGNED_INT, nullptr);
    }

    auto opengl_renderer_api::set_viewport(u32 x, u32 y, u32 width, u32 height) -> void
    {
        glViewport(x, y, width, height);
    }
}
