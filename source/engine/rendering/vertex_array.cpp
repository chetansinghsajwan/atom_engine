module atom.engine:rendering.vertex_array.impl;
import :rendering.vertex_array;

import atom.core;
import :rendering.renderer_api;
import :opengl.vertex_array;

namespace atom::engine
{
    auto vertex_array::create() -> vertex_array*
    {
        switch (renderer_api::get_api())
        {
            case renderer_api::api::opengl: return new opengl_vertex_array();
            case renderer_api::api::none:   ATOM_PANIC("renderer_api::api::none is not supported."); break;
            default:                   ATOM_PANIC("invalid renderer_api type."); break;
        }

        return nullptr;
    }
}
