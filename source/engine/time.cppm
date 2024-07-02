export module atom.engine:time;

import atom_core;

namespace atom::engine
{
    export class time_step
    {
    public:
        time_step(f32 seconds)
            : _seconds(seconds)
        {}

    public:
        auto get_seconds() const -> f32
        {
            return _seconds;
        }

        auto get_milliseconds() const -> f32
        {
            return _seconds * 1000;
        }

    private:
        f32 _seconds;
    };
}
