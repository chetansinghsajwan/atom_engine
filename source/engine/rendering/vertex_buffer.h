#pragma once
#include "atom.core.h"

namespace atom::engine
{
    class vertex_buffer
    {
    public:
        static auto create(float* vertices, u32 count) -> vertex_buffer*;

    public:
        virtual ~vertex_buffer() {}

    public:
        virtual auto bind() const -> void = 0;
        virtual auto unbind() const -> void = 0;
        virtual auto get_count() const -> u32 = 0;
    };
}
