module;
#include "GLFW/glfw3.h"

export module atom.engine:glfw_mouse_button_code_conversions;
import :mouse_button_codes;
import atom.core;

namespace atom::engine
{
    constexpr auto convert_mouse_button_code_atom_to_glfw(mouse_button_code button) -> int
    {
        struct conversion_map
        {
            constexpr conversion_map()
                : map()
            {
                map[usize::unwrapped_type(mouse_button_code::n0)] = GLFW_MOUSE_BUTTON_1;
                map[usize::unwrapped_type(mouse_button_code::n1)] = GLFW_MOUSE_BUTTON_2;
                map[usize::unwrapped_type(mouse_button_code::n2)] = GLFW_MOUSE_BUTTON_3;
                map[usize::unwrapped_type(mouse_button_code::n3)] = GLFW_MOUSE_BUTTON_4;
                map[usize::unwrapped_type(mouse_button_code::n4)] = GLFW_MOUSE_BUTTON_5;
                map[usize::unwrapped_type(mouse_button_code::n5)] = GLFW_MOUSE_BUTTON_6;
                map[usize::unwrapped_type(mouse_button_code::n6)] = GLFW_MOUSE_BUTTON_7;
                map[usize::unwrapped_type(mouse_button_code::n7)] = GLFW_MOUSE_BUTTON_8;
            }

            int map[usize::unwrapped_type(mouse_button_code::MAX) + 1];
        };

        constexpr auto map = conversion_map();
        return map.map[usize::unwrapped_type(button)];
    }

    constexpr auto convert_mouse_button_code_glfw_to_atom(int button) -> mouse_button_code
    {
        struct conversion_map
        {
            consteval conversion_map()
                : map()
            {
                map[GLFW_MOUSE_BUTTON_1] = mouse_button_code::n0;
                map[GLFW_MOUSE_BUTTON_2] = mouse_button_code::n1;
                map[GLFW_MOUSE_BUTTON_3] = mouse_button_code::n2;
                map[GLFW_MOUSE_BUTTON_4] = mouse_button_code::n3;
                map[GLFW_MOUSE_BUTTON_5] = mouse_button_code::n4;
                map[GLFW_MOUSE_BUTTON_6] = mouse_button_code::n5;
                map[GLFW_MOUSE_BUTTON_7] = mouse_button_code::n6;
                map[GLFW_MOUSE_BUTTON_8] = mouse_button_code::n7;
            }

            mouse_button_code map[GLFW_MOUSE_BUTTON_LAST + 1];
        };

        contracts::debug_expects(
            button >= 0 && button <= GLFW_MOUSE_BUTTON_LAST, "glfw button is out of range.");

        constexpr auto map = conversion_map();
        return map.map[button];
    }

    constexpr auto convert_mouse_button_state_atom_to_glfw(mouse_button_state state) -> int
    {
        struct conversion_map
        {
            consteval conversion_map()
            {
                map[usize::unwrapped_type(mouse_button_state::up)] = GLFW_RELEASE;
                map[usize::unwrapped_type(mouse_button_state::pressed)] = GLFW_PRESS;
                map[usize::unwrapped_type(mouse_button_state::down)] = GLFW_PRESS;
                map[usize::unwrapped_type(mouse_button_state::released)] = GLFW_RELEASE;
            }

            int map[usize::unwrapped_type(mouse_button_state::MAX) + 1];
        };

        constexpr auto map = conversion_map();
        return map.map[usize::unwrapped_type(state)];
    }

    constexpr auto convert_mouse_button_state_glfw_to_atom(int state) -> mouse_button_state
    {
        struct conversion_map
        {
            consteval conversion_map()
            {
                map[GLFW_PRESS] = mouse_button_state::pressed;
                map[GLFW_RELEASE] = mouse_button_state::released;
            }

            mouse_button_state map[2];
        };

        contracts::debug_expects(state >= 0 && state <= GLFW_PRESS, "glfw state is out of range.");

        constexpr auto map = conversion_map();
        return map.map[state];
    }
}
