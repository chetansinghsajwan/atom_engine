module atom.engine:rendering.vertex_buffer.impl;
import :rendering.vertex_buffer;

import atom.core;
import :rendering.renderer_api;
import :opengl.vertex_buffer;

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
