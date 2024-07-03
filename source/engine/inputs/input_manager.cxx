module atom_engine:inputs.input_manager.impl;
import :inputs.input_manager;

import :glfw;

namespace atom::engine
{
    auto input_manager::initialize() -> void
    {
        _impl = new glfw_input_manager_impl();
    }

    auto input_manager::finalize() -> void
    {
        delete _impl;
    }
}
