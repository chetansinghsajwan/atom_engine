module atom.engine:rendering.frame_buffer.impl;
import :rendering.frame_buffer;

import atom.core;
import :opengl.frame_buffer;
import :rendering.renderer_api;

namespace atom::engine
{
    auto frame_buffer::create(const frame_buffer_specs& specs) -> frame_buffer*
    {
        switch (renderer_api::get_api())
        {
            case renderer_api::api::opengl: return new opengl_frame_buffer(specs);
            case renderer_api::api::none:
                ATOM_PANIC("renderer_api::api::none is not supported.");
                break;
            default: ATOM_PANIC("invalid renderer_api type."); break;
        }

        return nullptr;
    }
}
