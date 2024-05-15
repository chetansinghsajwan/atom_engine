export module atom.engine:inputs.mouse_buttons;

namespace atom::engine
{
    export enum class mouse_button_code
    {
        unknown,
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

    export enum class mouse_button_state
    {
        up,
        pressed,
        down,
        released,

        MAX = released
    };
}