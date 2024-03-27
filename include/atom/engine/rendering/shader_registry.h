#pragma once
#include "atom/engine/rendering/shader.h"

namespace atom::engine
{
    class shader_registry
    {
    public:
        static auto initialize() -> void;
        static auto finalize() -> void;
        static auto register_(
            string_view name, class shader* shader) -> result<void, value_exists_error>;
        static auto register_override(string_view name, class shader* shader) -> void;
        static auto get_name(class shader* shader) -> string_view;
        static auto get_shader(string_view name) -> shader*;
        static auto has_name(string_view name) -> bool;
        static auto has_shader(class shader* shader) -> bool;
    };
}
