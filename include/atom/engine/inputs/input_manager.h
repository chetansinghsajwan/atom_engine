#pragma once
#include "atom.core.h"
#include "atom/engine/inputs/input_manager_impl.h"

namespace atom::engine
{
    class input_manager
    {
    public:
        static auto initialize() -> void;

        static auto finalize() -> void;

        static auto get_devices() -> array_view<input_device*>
        {
            return _impl->get_devices();
        }

    private:
        static inline input_manager_impl* _impl;
    };
}
