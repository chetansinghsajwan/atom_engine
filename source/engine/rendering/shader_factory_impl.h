#pragma once
#include "atom/engine/rendering/shader.h"

namespace atom::engine
{
    class shader_factory_impl
    {
    public:
        virtual ~shader_factory_impl() {}

    public:
        virtual auto create(string_view vertex_source, string_view fragment_source) -> shader* = 0;
        virtual auto destroy(shader* instance) -> void = 0;
    };
}
