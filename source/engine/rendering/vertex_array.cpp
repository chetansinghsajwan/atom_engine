#include "vertex_array.h"
#include "engine/rendering/renderer.h"
#include "engine/opengl/opengl_vertex_array.h"

namespace atom::engine
{
    auto vertex_array::create() -> vertex_array*
    {
        switch (renderer::get_api())
        {
            case renderer_api::opengl: return new opengl_vertex_array();
            case renderer_api::none:   ATOM_PANIC("renderer_api::none is not supported."); break;
            default:                   ATOM_PANIC("invalid renderer_api type."); break;
        }

        return nullptr;
    }
}
