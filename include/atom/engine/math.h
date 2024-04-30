#pragma once
#include "atom.core.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace atom::engine
{
    class vec2
    {
    public:
        constexpr vec2()
            : x(0)
            , y(0)
        {}

        constexpr vec2(f64 x, f64 y)
            : x(x)
            , y(y)
        {}

    public:
        f64 x;
        f64 y;
    };

    using vec4 = glm::vec4;

    using namespace ::glm;
}
