export module atom.engine:rendering.orthographic_camera;

import :math;

namespace atom::engine
{
    class orthographic_camera
    {
    public:
        orthographic_camera(float left, float right, float bottom, float top)
            : _projection_matrix(math::ortho(left, right, bottom, top, -1.0f, 1.0f))
            , _view_matrix(1.0f)
            , _position(0, 0, 0)
            , _rotation(0)
        {
            _view_projection_matrix = _projection_matrix * _view_matrix;
        }

    public:
        auto set_position(vec3 position) -> void
        {
            _position = position;
            _recalculate_view_matrix();
        }

        auto get_position() const -> const vec3&
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
            _projection_matrix = math::ortho(left, right, bottom, top, -1.0f, 1.0f);
        }

        auto get_projection_matrix() const -> const mat4&
        {
            return _projection_matrix;
        }

        auto get_view_matrix() const -> const mat4&
        {
            return _view_matrix;
        }

        auto get_view_projection_matrix() const -> const mat4&
        {
            return _view_projection_matrix;
        }

    private:
        auto _recalculate_view_matrix() -> void
        {
            mat4 transform = math::translate(mat4(1.0f), _position)
                             * math::rotate(mat4(1.0f), math::radians(_rotation), vec3(0, 0, 1));

            _view_matrix = math::inverse(transform);
            _view_projection_matrix = _projection_matrix * _view_matrix;
        }

    private:
        mat4 _projection_matrix;
        mat4 _view_matrix;
        mat4 _view_projection_matrix;

        vec3 _position;
        float _rotation;
    };
}
