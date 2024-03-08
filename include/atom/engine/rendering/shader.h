#pragma once
#include "atom.core.h"

namespace atom::engine
{
    class shader
    {
    public:
        virtual ~shader() {}

    public:
        virtual auto bind() -> void = 0;
        virtual auto unbind() -> void = 0;
    };
}
