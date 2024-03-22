#include "orthographic_camera.h"

namespace atom::engine
{
    orthographic_camera::orthographic_camera(float left, float right, float bottom, float top)
        : _projection_matrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
        , _view_matrix(1.0f)
        , _position(0, 0, 0)
        , _rotation(0)
    {
        _view_projection_matrix = _projection_matrix * _view_matrix;
    }

    auto orthographic_camera::_recalculate_view_matrix() -> void
    {
        glm::mat4 transform =
            glm::translate(glm::mat4(1.0f), _position)
            * glm::rotate(glm::mat4(1.0f), glm::radians(_rotation), glm::vec3(0, 0, 1));

        _view_matrix = glm::inverse(transform);
        _view_projection_matrix = _projection_matrix * _view_matrix;
    }
}
