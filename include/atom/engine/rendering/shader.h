#pragma once
#include "atom.core.h"
#include "atom/engine/math.h"

namespace atom::engine
{
    class shader
    {
    public:
        virtual ~shader() {}

    public:
        virtual auto bind() -> void = 0;
        virtual auto unbind() -> void = 0;
        virtual auto upload_uniform_mat4(string_view name, const glm::mat4& mat) -> void = 0;
    };
}
