export module atom.engine:rendering.scene_camera;

import atom.core;
import :math;
import :rendering.camera;

namespace atom::engine
{
    export class scene_camera: public camera
    {
    public:
        scene_camera()
        {
            _recalculate_projection();
        }

        virtual ~scene_camera() = default;

    public:
        auto set_orthographic(float size, float near_clip, float far_clip) -> void
        {
            _orthographic_size = size;
            _orthographic_near = near_clip;
            _orthographic_far = far_clip;
            _recalculate_projection();
        }

        auto set_viewport_size(uint32_t width, uint32_t height) -> void
        {
            _aspect_ratio = (float)width / (float)height;
            _recalculate_projection();
        }

        auto get_orthographic_size() const -> float
        {
            return _orthographic_size;
        }

        auto set_orthographic_size(float size) -> void
        {
            _orthographic_size = size;
            _recalculate_projection();
        }

    private:
        auto _recalculate_projection() -> void
        {
            float ortho_left = -_orthographic_size * _aspect_ratio * .5;
            float ortho_right = _orthographic_size * _aspect_ratio * .5;
            float ortho_bottom = -_orthographic_size * .5;
            float ortho_top = _orthographic_size * .5;

            _projection = math::ortho(ortho_left, ortho_right, ortho_bottom, ortho_top,
                _orthographic_near, _orthographic_far);
        }

    private:
        float _orthographic_size = 10.0f;
        float _orthographic_near = -1.0f;
        float _orthographic_far = 1.0f;
        float _aspect_ratio = 0.0f;
    };
}
