export module atom.engine:math;
import atom.core;

namespace atom::engine
{
    export class vec2
    {
    public:
        constexpr vec2()
            : x(0)
            , y(0)
        {}

        constexpr vec2(f64 x, f64 y)
            : x(x)
            , y(y)
        {}

    public:
        f64 x;
        f64 y;
    };
}
