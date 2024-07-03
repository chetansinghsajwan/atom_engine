module;
#include "imgui.h"

export module atom_engine:imgui.mouse_conversions;

import :inputs;

namespace atom::engine
{
    /// --------------------------------------------------------------------------------------------
    /// returns `ImGuiMouseButton_COUNT` if no match found.
    /// --------------------------------------------------------------------------------------------
    constexpr auto convert_mouse_button_atom_to_imgui(
        mouse_button_code button) -> ImGuiMouseButton_;

    /// --------------------------------------------------------------------------------------------
    /// returns `mouse_button_code::unknown` if no match found.
    /// --------------------------------------------------------------------------------------------
    constexpr auto convert_mouse_button_imgui_to_atom(
        ImGuiMouseButton_ button) -> mouse_button_code;
}
