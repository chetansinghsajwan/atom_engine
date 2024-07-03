export module atom_engine:rendering.scene_camera;

import atom_core;
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
        auto set_orthographic(f32 size, f32 near_clip, f32 far_clip) -> void
        {
            _orthographic_size = size;
            _orthographic_near = near_clip;
            _orthographic_far = far_clip;
            _recalculate_projection();
        }

        auto set_viewport_size(u32 width, u32 height) -> void
        {
            _aspect_ratio = (f32)width / (f32)height;
            _recalculate_projection();
        }

        auto get_orthographic_size() const -> f32
        {
            return _orthographic_size;
        }

        auto set_orthographic_size(f32 size) -> void
        {
            _orthographic_size = size;
            _recalculate_projection();
        }

    private:
        auto _recalculate_projection() -> void
        {
            f32 ortho_left = -_orthographic_size * _aspect_ratio * .5;
            f32 ortho_right = _orthographic_size * _aspect_ratio * .5;
            f32 ortho_bottom = -_orthographic_size * .5;
            f32 ortho_top = _orthographic_size * .5;

            _projection = math::ortho(ortho_left, ortho_right, ortho_bottom, ortho_top,
                _orthographic_near, _orthographic_far);
        }

    private:
        f32 _orthographic_size = 10.0f;
        f32 _orthographic_near = -1.0f;
        f32 _orthographic_far = 1.0f;
        f32 _aspect_ratio = 0.0f;
    };
}
