#pragma once
#include "atom.engine.h"

namespace atom::engine
{
    class texture
    {
    public:
        virtual ~texture() {}

    public:
        virtual auto get_height() const -> u32 = 0;
        virtual auto get_width() const -> u32 = 0;
        virtual auto bind(u32 slot = 0) -> void = 0;
        virtual auto set_data(const void* data, u32 size) -> void = 0;
    };
}
