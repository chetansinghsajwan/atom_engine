export module atom.engine:rendering.camera;

import :math;

namespace atom::engine
{
    class camera
    {
    public:
        camera() {}

        virtual ~camera() = default;

    public:
        auto get_projection() const -> const mat4&
        {
            return _projection;
        }

    protected:
        mat4 _projection = mat4{ 1 };
    };
}
