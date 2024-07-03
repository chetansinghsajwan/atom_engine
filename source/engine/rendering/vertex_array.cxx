module atom_engine:rendering.vertex_array.impl;
import :rendering.vertex_array;

import atom_core;
import :rendering.renderer_api;
import :opengl.vertex_array;

namespace atom::engine
{
    auto vertex_array::create() -> vertex_array*
    {
        switch (renderer_api::get_api())
        {
            case renderer_api::api::opengl: return new opengl_vertex_array();
            case renderer_api::api::none:
                contract_panic("renderer_api::api::none is not supported.");
                break;
            default: contract_panic("invalid renderer_api type."); break;
        }

        return nullptr;
    }
}
