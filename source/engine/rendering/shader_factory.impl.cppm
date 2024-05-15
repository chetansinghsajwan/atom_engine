module atom.engine:rendering.shader_factory.impl;
import :rendering.shader_factory;

import :rendering.shader_factory_impl;
import :opengl.shader_factory_impl;

namespace atom::engine
{
    auto shader_factory::_create_impl() -> shader_factory_impl*
    {
        return new opengl_shader_factory_impl();
    }
}
