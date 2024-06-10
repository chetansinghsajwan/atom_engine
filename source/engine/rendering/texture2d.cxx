module atom.engine:rendering.texture2d.impl;
import :rendering.texture2d;

import atom.core;
import :rendering.renderer_api;
import :opengl.texture2d;

namespace atom::engine
{
    auto texture2d::create(u32 width, u32 height) -> texture2d*
    {
        switch (renderer_api::get_api())
        {
            case renderer_api::api::opengl: return new opengl_texture2d(width, height);
            case renderer_api::api::none:
                contract_panic("renderer_api::api::none is not supported.");
                break;
            default: contract_panic("invalid renderer_api type."); break;
        }

        return nullptr;
    }

    auto texture2d::create(string_view file_path) -> texture2d*
    {
        switch (renderer_api::get_api())
        {
            case renderer_api::api::opengl: return new opengl_texture2d(file_path);
            case renderer_api::api::none:
                contract_panic("renderer_api::api::none is not supported.");
                break;
            default: contract_panic("invalid renderer_api type."); break;
        }

        return nullptr;
    }
}
