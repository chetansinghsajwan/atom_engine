#pragma once
#include "atom/engine/rendering/shader.h"

namespace atom::engine
{
    class shader_factory
    {
    public:
        static auto initialize() -> void;
        static auto finalize() -> void;
        static auto create_from_file(string_view path) -> shader*;
        static auto create_from_source(string_view vertex_source, string_view fragment_source)
            -> shader*;
        static auto destroy(shader* instance) -> void;
    };
}
