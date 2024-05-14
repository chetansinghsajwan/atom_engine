#pragma once
// #include "atom.core.h"
#include "engine/rendering/buffer_layout.h"

namespace atom::engine
{
    class vertex_buffer
    {
    public:
        static auto create_with_size(u32 size) -> vertex_buffer*;
        static auto create(float* vertices, u32 count) -> vertex_buffer*;

    public:
        virtual ~vertex_buffer() {}

    public:
        virtual auto bind() const -> void = 0;
        virtual auto unbind() const -> void = 0;
        virtual auto get_count() const -> u32 = 0;
        virtual auto set_layout(const buffer_layout& layout) -> void = 0;
        virtual auto get_layout() -> buffer_layout& = 0;
        virtual auto set_data(const void* data, u32 size) -> void = 0;
    };
}
