export module atom_engine:rendering.camera;

import :math;

namespace atom::engine
{
    class camera
    {
    public:
        camera() {}

        virtual ~camera() = default;

    public:
        auto get_projection() const -> const f32mat4&
        {
            return _projection;
        }

    protected:
        f32mat4 _projection = f32mat4{ 1 };
    };
}
