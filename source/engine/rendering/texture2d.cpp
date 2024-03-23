#include "atom/engine/rendering/texture2d.h"
#include "engine/rendering/renderer_api.h"
#include "engine/opengl/opengl_texture2d.h"

namespace atom::engine
{
    auto texture2d::create(string_view file_path) -> texture2d*
    {
        switch (renderer_api::get_api())
        {
            case renderer_api::api::opengl: return new opengl_texture2d(file_path);
            case renderer_api::api::none:   ATOM_PANIC("renderer_api::api::none is not supported."); break;
            default:                   ATOM_PANIC("invalid renderer_api type."); break;
        }

        return nullptr;
    }
}
