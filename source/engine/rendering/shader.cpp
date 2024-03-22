#include "atom/engine/rendering/shader.h"
#include "engine/rendering/renderer_api.h"
#include "engine/opengl/opengl_shader.h"

namespace atom::engine
{
    auto shader::create(string_view vertex_src, string_view fragement_src) -> shader*
    {
        switch (renderer_api::get_api())
        {
            case renderer_api::api::opengl: return new opengl_shader(vertex_src, fragement_src);
            case renderer_api::api::none:
                ATOM_PANIC("renderer_api::api::none is not supported.");
                break;
            default: ATOM_PANIC("invalid renderer_api type."); break;
        }

        return nullptr;
    }
}
