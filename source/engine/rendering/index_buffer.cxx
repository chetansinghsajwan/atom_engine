module atom_engine:rendering.index_buffer.impl;
import :rendering.index_buffer;

import atom_core;
import :rendering.renderer_api;
import :opengl.index_buffer;

namespace atom::engine
{
    auto index_buffer::create(u32* indices, u32 count) -> index_buffer*
    {
        switch (renderer_api::get_api())
        {
            case renderer_api::api::opengl: return new opengl_index_buffer(indices, count);
            case renderer_api::api::none:
                contract_panic("renderer_api::api::none is not supported.");
                break;
            default: contract_panic("invalid renderer_api type."); break;
        }

        return nullptr;
    }
}
