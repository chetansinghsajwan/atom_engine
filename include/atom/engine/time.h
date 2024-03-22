#pragma once

namespace atom::engine
{
    class time_stemp
    {
    public:
        time_stemp(float seconds)
            : _seconds(seconds)
        {}

    public:
        auto get_seconds() const -> float
        {
            return _seconds;
        }

        auto get_milliseconds() const -> float
        {
            return _seconds * 1000;
        }

    private:
        float _seconds;
    };
}
