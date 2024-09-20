module;
#include "imgui.h"

module atom.engine:imgui.mouse_conversions.impl;

import :inputs;

namespace atom::engine
{
    /// --------------------------------------------------------------------------------------------
    /// returns `ImGuiMouseButton_COUNT` if no match found.
    /// --------------------------------------------------------------------------------------------
    constexpr auto convert_mouse_button_atom_to_imgui(mouse_button_code button) -> ImGuiMouseButton_
    {
        switch (button)
        {
            case mouse_button_code::left:   return ImGuiMouseButton_Left;
            case mouse_button_code::right:  return ImGuiMouseButton_Right;
            case mouse_button_code::middle: return ImGuiMouseButton_Middle;
            case mouse_button_code::n3:     return ImGuiMouseButton_(3);
            case mouse_button_code::n4:     return ImGuiMouseButton_(4);
            default:                        return ImGuiMouseButton_COUNT;
        }
    }

    /// --------------------------------------------------------------------------------------------
    /// returns `mouse_button_code::unknown` if no match found.
    /// --------------------------------------------------------------------------------------------
    constexpr auto convert_mouse_button_imgui_to_atom(ImGuiMouseButton_ button) -> mouse_button_code
    {
        switch (button)
        {
            case ImGuiMouseButton_Left:   return mouse_button_code::left;
            case ImGuiMouseButton_Right:  return mouse_button_code::right;
            case ImGuiMouseButton_Middle: return mouse_button_code::middle;
            default:                      return mouse_button_code::unknown;
        }
    }
}
