import atom.core;
import atom.logging;

#include "engine/rendering/scene_camera.h"

namespace atom::engine
{
    auto scene_camera::_recalculate_projection() -> void
    {
        float ortho_left = -_orthographic_size * _aspect_ratio * .5;
        float ortho_right = _orthographic_size * _aspect_ratio * .5;
        float ortho_bottom = -_orthographic_size * .5;
        float ortho_top = _orthographic_size * .5;

        _projection = glm::ortho(ortho_left, ortho_right, ortho_bottom, ortho_top,
            _orthographic_near, _orthographic_far);
    }
}
