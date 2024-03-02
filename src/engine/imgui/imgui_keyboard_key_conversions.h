#pragma once
#include "atom/engine/inputs/keyboard_keys.h"

#include "imgui.h"

namespace atom::engine
{
    static auto imgui_atom_key_to_imgui_key(keyboard_key_code key) -> ImGuiKey
    {
        // todo: implement this.
        return ImGuiKey_None;
    }

    static auto imgui_atom_button_to_imgui_button(mouse_button_code button) -> ImGuiMouseButton_
    {
        // todo: implement this.
        return ImGuiMouseButton_COUNT;
    }

    static auto imgui_is_atom_keyboard_key_state_down(keyboard_key_state state) -> bool
    {
        return true;
    }

    static auto imgui_is_atom_mouse_button_state_down(mouse_button_state state) -> bool
    {
        return true;
    }
}
