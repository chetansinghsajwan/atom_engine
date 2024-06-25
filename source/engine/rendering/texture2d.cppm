export module atom.engine:rendering.texture2d;

import atom.core;
import :rendering.texture;

namespace atom::engine
{
    export class texture2d: public texture
    {
    public:
        texture2d(texture_format format)
            : texture{ format }
        {}

        ~texture2d() {}
    };
}
