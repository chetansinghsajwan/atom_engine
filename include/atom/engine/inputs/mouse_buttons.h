#pragma once

namespace atom::engine
{
    enum class mouse_button_code
    {
        n0,
        n1,
        n2,
        n3,
        n4,
        n5,
        n6,
        n7,
        left = n0,
        right = n1,
        middle = n2,

        MAX = n7,
    };

    enum class mouse_button_state
    {
        up,
        pressed,
        down,
        released,

        MAX = released
    };
}