export module atom_engine:rendering.texture2d;

import atom_core;
import :math;
import :rendering.texture;

namespace atom::engine
{
    export struct texture2d: public texture
    {
    public:
        texture2d(texture_format format, u32vec2 size);
        virtual ~texture2d();
    };
}
