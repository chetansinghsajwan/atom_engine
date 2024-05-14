import atom.core;
import atom.logging;

#include "vertex_buffer.h"
#include "engine/opengl/opengl_vertex_buffer.h"
#include "engine/rendering/renderer.h"

namespace atom::engine
{
    auto vertex_buffer::create_with_size(u32 size) -> vertex_buffer*
    {
        switch (renderer_api::get_api())
        {
            case renderer_api::api::opengl: return new opengl_vertex_buffer(size);
            case renderer_api::api::none:
                ATOM_PANIC("renderer_api::api::none is not supported.");
                break;
            default: ATOM_PANIC("invalid renderer_api type."); break;
        }

        return nullptr;
    }
    
    auto vertex_buffer::create(float* vertices, u32 count) -> vertex_buffer*
    {
        switch (renderer_api::get_api())
        {
            case renderer_api::api::opengl: return new opengl_vertex_buffer(vertices, count);
            case renderer_api::api::none:
                ATOM_PANIC("renderer_api::api::none is not supported.");
                break;
            default: ATOM_PANIC("invalid renderer_api type."); break;
        }

        return nullptr;
    }
}
