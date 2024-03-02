#include "atom/engine/inputs/input_manager.h"
#include "glfw/glfw_input_manager.h"

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
