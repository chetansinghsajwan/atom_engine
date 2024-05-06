#pragma once
#include "atom.core.h"

namespace atom::engine
{
    struct frame_buffer_specs
    {
        u32 width;
        u32 height;
        u32 samples = 1;
        bool swap_chain_target = false;
    };

    class frame_buffer
    {
    public:
        virtual ~frame_buffer() {}

    public:
        static auto create(const frame_buffer_specs& specs) -> frame_buffer*;

    public:
        virtual auto bind() -> void = 0;
        virtual auto unbind() -> void = 0;
        virtual auto get_specs() const -> const frame_buffer_specs& = 0;
        virtual auto get_color_attachment() const -> u32 = 0;
    };
}
