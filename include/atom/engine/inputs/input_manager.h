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

    private:
        static inline input_manager_impl* _impl;
    };
}
