#include "vertex_buffer.h"
#include "engine/opengl/opengl_vertex_buffer.h"
#include "engine/rendering/renderer.h"

namespace atom::engine
{
    auto vertex_buffer::create(float* vertices, u32 count) -> vertex_buffer*
    {
        switch (renderer::get_api())
        {
            case renderer_api::opengl: return new opengl_vertex_buffer(vertices, count);
            case renderer_api::none:   ATOM_PANIC("renderer_api::none is not supported."); break;
            default:                   ATOM_PANIC("invalid renderer_api type."); break;
        }

        return nullptr;
    }
}
