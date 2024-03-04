#pragma once

namespace atom::engine
{
    class graphics_context
    {
    public:
        virtual auto initialize() -> void = 0;
        virtual auto swap_buffers() -> void = 0;
    };
}
