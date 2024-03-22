#include "renderer.h"

namespace atom::engine
{
    auto renderer::begin_scene() -> void {}

    auto renderer::end_scene() -> void {}

    auto renderer::submit(vertex_array* arr) -> void
    {
        arr->bind();
        render_command::draw_indexed(arr);
    }
}
