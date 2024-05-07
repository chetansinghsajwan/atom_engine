#pragma once
#include "atom/engine/math.h"

namespace atom::engine
{
    class camera
    {
    public:
        camera(const mat4& projection)
            : _projection(projection)
        {}

        auto get_projection() const -> const mat4&
        {
            return _projection;
        }

    private:
        glm::mat4 _projection;
    };
}
