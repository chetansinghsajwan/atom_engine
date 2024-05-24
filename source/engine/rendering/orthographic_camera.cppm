export module atom.engine:rendering.orthographic_camera;

import atom.core;
import :math;

namespace atom::engine
{
    class orthographic_camera
    {
    public:
        orthographic_camera(f32 left, f32 right, f32 bottom, f32 top)
            : _projection_matrix(math::ortho(left, right, bottom, top, -1.0f, 1.0f))
            , _view_matrix(1.0f)
            , _position{ 0 }
            , _rotation( 0 )
        {
            _view_projection_matrix = _projection_matrix * _view_matrix;
        }

    public:
        auto set_position(f32vec3 position) -> void
        {
            _position = position;
            _recalculate_view_matrix();
        }

        auto get_position() const -> const f32vec3&
        {
            return _position;
        }

        auto set_rotation(f32 rotation) -> void
        {
            _rotation = rotation;
            _recalculate_view_matrix();
        }

        auto get_rotation() const -> f32
        {
            return _rotation;
        }

        auto set_projection(f32 left, f32 right, f32 bottom, f32 top) -> void
        {
            _projection_matrix = math::ortho(left, right, bottom, top, -1.0f, 1.0f);
        }

        auto get_projection_matrix() const -> const f32mat4&
        {
            return _projection_matrix;
        }

        auto get_view_matrix() const -> const f32mat4&
        {
            return _view_matrix;
        }

        auto get_view_projection_matrix() const -> const f32mat4&
        {
            return _view_projection_matrix;
        }

    private:
        auto _recalculate_view_matrix() -> void
        {
            f32mat4 transform = math::translate(f32mat4{ 1 }, _position)
                             * math::rotate(f32mat4{ 1 }, math::radians(_rotation), f32vec3{ 0, 0, 1 });

            _view_matrix = math::inverse(transform);
            _view_projection_matrix = _projection_matrix * _view_matrix;
        }

    private:
        f32mat4 _projection_matrix;
        f32mat4 _view_matrix;
        f32mat4 _view_projection_matrix;
        f32vec3 _position;
        float _rotation;
    };
}
