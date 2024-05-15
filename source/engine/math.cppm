module;

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

export module atom.engine:math;

import atom.core;

export namespace atom::engine
{
    using glm::mat4;
    using glm::vec2;
    using glm::vec3;
    using glm::vec4;

    using glm::operator+;
    using glm::operator-;
    using glm::operator*;
    using glm::operator/;
    using glm::operator==;
    using glm::operator!=;

    namespace math
    {
        using namespace atom::math;

        using glm::degrees;
        using glm::inverse;
        using glm::ortho;
        using glm::radians;
        using glm::rotate;
        using glm::scale;
        using glm::translate;
        using glm::value_ptr;
    }
}
