module;
#include "imgui.h"

export module atom_engine:imgui.keyboard_conversions;

import :inputs;

namespace atom::engine
{
    /// --------------------------------------------------------------------------------------------
    /// returns `ImGuiKey_None` if no match found.
    /// --------------------------------------------------------------------------------------------
    constexpr auto convert_keyboard_key_code_atom_to_imgui(keyboard_key_code key) -> ImGuiKey;

    /// --------------------------------------------------------------------------------------------
    /// returns `keyboard_key_code::unknown` if no match found.
    /// --------------------------------------------------------------------------------------------
    constexpr auto convert_keyboard_key_code_imgui_to_atom(ImGuiKey key) -> keyboard_key_code;
}
