#pragma once
#include "atom.core.h"
#include "atom/engine/inputs/mouse_buttons.h"

#include "GLFW/glfw3.h"

/// ------------------------------------------------------------------------------------------------
/// @todo maybe convert panics to debug panics, return unknown values in release.
/// ------------------------------------------------------------------------------------------------
namespace atom::engine
{
    constexpr auto convert_mouse_button_code_atom_to_glfw(mouse_button_code button) -> int
    {
        switch (button)
        {
            case mouse_button_code::n0: return GLFW_MOUSE_BUTTON_1;
            case mouse_button_code::n1: return GLFW_MOUSE_BUTTON_2;
            case mouse_button_code::n2: return GLFW_MOUSE_BUTTON_3;
            case mouse_button_code::n3: return GLFW_MOUSE_BUTTON_4;
            case mouse_button_code::n4: return GLFW_MOUSE_BUTTON_5;
            case mouse_button_code::n5: return GLFW_MOUSE_BUTTON_6;
            case mouse_button_code::n6: return GLFW_MOUSE_BUTTON_7;
            case mouse_button_code::n7: return GLFW_MOUSE_BUTTON_8;
            default:
            {
                ATOM_PANIC("invalid button.", button);
            }
        }
    }

    constexpr auto convert_mouse_button_code_glfw_to_atom(int button) -> mouse_button_code
    {
        switch (button)
        {
            case GLFW_MOUSE_BUTTON_1: return mouse_button_code::n0;
            case GLFW_MOUSE_BUTTON_2: return mouse_button_code::n1;
            case GLFW_MOUSE_BUTTON_3: return mouse_button_code::n2;
            case GLFW_MOUSE_BUTTON_4: return mouse_button_code::n3;
            case GLFW_MOUSE_BUTTON_5: return mouse_button_code::n4;
            case GLFW_MOUSE_BUTTON_6: return mouse_button_code::n5;
            case GLFW_MOUSE_BUTTON_7: return mouse_button_code::n6;
            case GLFW_MOUSE_BUTTON_8: return mouse_button_code::n7;
            default:
            {
                ATOM_PANIC("invalid button.", button);
            }
        }
    }

    constexpr auto convert_mouse_button_state_atom_to_glfw(mouse_button_state state) -> int
    {
        switch (state)
        {
            case mouse_button_state::up:       return GLFW_RELEASE;
            case mouse_button_state::pressed:  return GLFW_PRESS;
            case mouse_button_state::down:     return GLFW_PRESS;
            case mouse_button_state::released: return GLFW_RELEASE;
            default:
            {
                ATOM_PANIC("invalid state.", state);
            }
        }
    }

    constexpr auto convert_mouse_button_state_glfw_to_atom(int state) -> mouse_button_state
    {
        switch (state)
        {
            case GLFW_PRESS:   return mouse_button_state::pressed;
            case GLFW_RELEASE: return mouse_button_state::released;
            default:
            {
                ATOM_PANIC("invalid state.", state);
            }
        }
    }
}
