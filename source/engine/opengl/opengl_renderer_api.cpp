#include "opengl_renderer_api.h"
#include "glad/glad.h"

namespace atom::engine
{
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
}
