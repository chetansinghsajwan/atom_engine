#pragma once
#include "atom/engine/math.h"

namespace atom::engine
{
    class orthographic_camera
    {
    public:
        orthographic_camera(float left, float right, float bottom, float top);

    public:
        auto set_position(glm::vec3 position) -> void
        {
            _position = position;
            _recalculate_view_matrix();
        }

        auto get_position() const -> const glm::vec3&
        {
            return _position;
        }

        auto set_rotation(float rotation) -> void
        {
            _rotation = rotation;
            _recalculate_view_matrix();
        }

        auto get_rotation() const -> float
        {
            return _rotation;
        }

        auto set_projection(float left, float right, float bottom, float top) -> void
        {
            _projection_matrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        }

        auto get_projection_matrix() const -> const glm::mat4&
        {
            return _projection_matrix;
        }

        auto get_view_matrix() const -> const glm::mat4&
        {
            return _view_matrix;
        }

        auto get_view_projection_matrix() const -> const glm::mat4&
        {
            return _view_projection_matrix;
        }

    private:
        auto _recalculate_view_matrix() -> void;

    private:
        glm::mat4 _projection_matrix;
        glm::mat4 _view_matrix;
        glm::mat4 _view_projection_matrix;

        glm::vec3 _position;
        float _rotation;
    };
}
