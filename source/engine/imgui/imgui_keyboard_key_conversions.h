#pragma once
#include "atom/engine/inputs/keyboard_keys.h"
#include "atom/engine/inputs/mouse_buttons.h"

#include "imgui.h"

/// ------------------------------------------------------------------------------------------------
/// @todo handle default cases.
/// ------------------------------------------------------------------------------------------------
namespace atom::engine
{
    /// --------------------------------------------------------------------------------------------
    /// returns `ImGuiKey_None` if no match found.
    /// --------------------------------------------------------------------------------------------
    static auto imgui_atom_key_to_imgui_key(keyboard_key_code key) -> ImGuiKey
    {
        switch (key)
        {
            case keyboard_key_code::unknown:       return ImGuiKey_None;
            case keyboard_key_code::space:         return ImGuiKey_Space;
            case keyboard_key_code::apostrophe:    return ImGuiKey_Apostrophe;
            case keyboard_key_code::comma:         return ImGuiKey_Comma;
            case keyboard_key_code::minus:         return ImGuiKey_Minus;
            case keyboard_key_code::preiod:        return ImGuiKey_Period;
            case keyboard_key_code::slash:         return ImGuiKey_Slash;
            case keyboard_key_code::n0:            return ImGuiKey_0;
            case keyboard_key_code::n1:            return ImGuiKey_1;
            case keyboard_key_code::n2:            return ImGuiKey_2;
            case keyboard_key_code::n3:            return ImGuiKey_3;
            case keyboard_key_code::n4:            return ImGuiKey_4;
            case keyboard_key_code::n5:            return ImGuiKey_5;
            case keyboard_key_code::n6:            return ImGuiKey_6;
            case keyboard_key_code::n7:            return ImGuiKey_7;
            case keyboard_key_code::n8:            return ImGuiKey_8;
            case keyboard_key_code::n9:            return ImGuiKey_9;
            case keyboard_key_code::semicolon:     return ImGuiKey_Semicolon;
            case keyboard_key_code::equal:         return ImGuiKey_Equal;
            case keyboard_key_code::a:             return ImGuiKey_A;
            case keyboard_key_code::b:             return ImGuiKey_B;
            case keyboard_key_code::c:             return ImGuiKey_C;
            case keyboard_key_code::d:             return ImGuiKey_D;
            case keyboard_key_code::e:             return ImGuiKey_E;
            case keyboard_key_code::f:             return ImGuiKey_F;
            case keyboard_key_code::g:             return ImGuiKey_G;
            case keyboard_key_code::h:             return ImGuiKey_H;
            case keyboard_key_code::i:             return ImGuiKey_I;
            case keyboard_key_code::j:             return ImGuiKey_J;
            case keyboard_key_code::k:             return ImGuiKey_K;
            case keyboard_key_code::l:             return ImGuiKey_L;
            case keyboard_key_code::m:             return ImGuiKey_M;
            case keyboard_key_code::n:             return ImGuiKey_N;
            case keyboard_key_code::o:             return ImGuiKey_O;
            case keyboard_key_code::p:             return ImGuiKey_P;
            case keyboard_key_code::q:             return ImGuiKey_Q;
            case keyboard_key_code::r:             return ImGuiKey_R;
            case keyboard_key_code::s:             return ImGuiKey_S;
            case keyboard_key_code::t:             return ImGuiKey_T;
            case keyboard_key_code::u:             return ImGuiKey_U;
            case keyboard_key_code::v:             return ImGuiKey_V;
            case keyboard_key_code::w:             return ImGuiKey_W;
            case keyboard_key_code::x:             return ImGuiKey_X;
            case keyboard_key_code::y:             return ImGuiKey_Y;
            case keyboard_key_code::z:             return ImGuiKey_Z;
            case keyboard_key_code::left_bracket:  return ImGuiKey_LeftBracket;
            case keyboard_key_code::backslash:     return ImGuiKey_Backslash;
            case keyboard_key_code::right_bracket: return ImGuiKey_RightBracket;
            case keyboard_key_code::grave_accent:  return ImGuiKey_GraveAccent;
            case keyboard_key_code::world_1:       return ImGuiKey_None;
            case keyboard_key_code::world_2:       return ImGuiKey_None;
            case keyboard_key_code::escape:        return ImGuiKey_Escape;
            case keyboard_key_code::enter:         return ImGuiKey_Enter;
            case keyboard_key_code::tab:           return ImGuiKey_Tab;
            case keyboard_key_code::backspace:     return ImGuiKey_Backspace;
            case keyboard_key_code::insert:        return ImGuiKey_Insert;
            case keyboard_key_code::del:           return ImGuiKey_Delete;
            case keyboard_key_code::right:         return ImGuiKey_RightArrow;
            case keyboard_key_code::left:          return ImGuiKey_LeftArrow;
            case keyboard_key_code::down:          return ImGuiKey_DownArrow;
            case keyboard_key_code::up:            return ImGuiKey_UpArrow;
            case keyboard_key_code::page_up:       return ImGuiKey_PageUp;
            case keyboard_key_code::page_down:     return ImGuiKey_PageDown;
            case keyboard_key_code::home:          return ImGuiKey_Home;
            case keyboard_key_code::end:           return ImGuiKey_End;
            case keyboard_key_code::caps_lock:     return ImGuiKey_CapsLock;
            case keyboard_key_code::scroll_lock:   return ImGuiKey_ScrollLock;
            case keyboard_key_code::num_lock:      return ImGuiKey_NumLock;
            case keyboard_key_code::print_screen:  return ImGuiKey_PrintScreen;
            case keyboard_key_code::pause:         return ImGuiKey_Pause;
            case keyboard_key_code::f1:            return ImGuiKey_F1;
            case keyboard_key_code::f2:            return ImGuiKey_F2;
            case keyboard_key_code::f3:            return ImGuiKey_F3;
            case keyboard_key_code::f4:            return ImGuiKey_F4;
            case keyboard_key_code::f5:            return ImGuiKey_F5;
            case keyboard_key_code::f6:            return ImGuiKey_F6;
            case keyboard_key_code::f7:            return ImGuiKey_F7;
            case keyboard_key_code::f8:            return ImGuiKey_F8;
            case keyboard_key_code::f9:            return ImGuiKey_F9;
            case keyboard_key_code::f10:           return ImGuiKey_F10;
            case keyboard_key_code::f11:           return ImGuiKey_F11;
            case keyboard_key_code::f12:           return ImGuiKey_F12;
            case keyboard_key_code::f13:           return ImGuiKey_F13;
            case keyboard_key_code::f14:           return ImGuiKey_F14;
            case keyboard_key_code::f15:           return ImGuiKey_F15;
            case keyboard_key_code::f16:           return ImGuiKey_F16;
            case keyboard_key_code::f17:           return ImGuiKey_F17;
            case keyboard_key_code::f18:           return ImGuiKey_F18;
            case keyboard_key_code::f19:           return ImGuiKey_F19;
            case keyboard_key_code::f20:           return ImGuiKey_F20;
            case keyboard_key_code::f21:           return ImGuiKey_F21;
            case keyboard_key_code::f22:           return ImGuiKey_F22;
            case keyboard_key_code::f23:           return ImGuiKey_F23;
            case keyboard_key_code::f24:           return ImGuiKey_F24;
            case keyboard_key_code::f25:           return ImGuiKey_None;
            case keyboard_key_code::kp_0:          return ImGuiKey_Keypad0;
            case keyboard_key_code::kp_1:          return ImGuiKey_Keypad1;
            case keyboard_key_code::kp_2:          return ImGuiKey_Keypad2;
            case keyboard_key_code::kp_3:          return ImGuiKey_Keypad3;
            case keyboard_key_code::kp_4:          return ImGuiKey_Keypad4;
            case keyboard_key_code::kp_5:          return ImGuiKey_Keypad5;
            case keyboard_key_code::kp_6:          return ImGuiKey_Keypad6;
            case keyboard_key_code::kp_7:          return ImGuiKey_Keypad7;
            case keyboard_key_code::kp_8:          return ImGuiKey_Keypad8;
            case keyboard_key_code::kp_9:          return ImGuiKey_Keypad9;
            case keyboard_key_code::kp_decimal:    return ImGuiKey_KeypadDecimal;
            case keyboard_key_code::kp_divide:     return ImGuiKey_KeypadDivide;
            case keyboard_key_code::kp_multiply:   return ImGuiKey_KeypadMultiply;
            case keyboard_key_code::kp_subtract:   return ImGuiKey_KeypadSubtract;
            case keyboard_key_code::kp_add:        return ImGuiKey_KeypadAdd;
            case keyboard_key_code::kp_enter:      return ImGuiKey_KeypadEnter;
            case keyboard_key_code::kp_equal:      return ImGuiKey_KeypadEqual;
            case keyboard_key_code::left_shift:    return ImGuiKey_LeftShift;
            case keyboard_key_code::left_control:  return ImGuiKey_LeftCtrl;
            case keyboard_key_code::left_alt:      return ImGuiKey_LeftAlt;
            case keyboard_key_code::left_super:    return ImGuiKey_LeftSuper;
            case keyboard_key_code::right_shift:   return ImGuiKey_RightShift;
            case keyboard_key_code::right_control: return ImGuiKey_RightCtrl;
            case keyboard_key_code::right_alt:     return ImGuiKey_RightAlt;
            case keyboard_key_code::right_super:   return ImGuiKey_RightSuper;
            case keyboard_key_code::menu:          return ImGuiKey_Menu;
            default:                               return ImGuiKey_None;
        }
    }

    /// --------------------------------------------------------------------------------------------
    /// returns `keyboard_key_code::unknown` is no match found.
    /// --------------------------------------------------------------------------------------------
    static auto imgui_imgui_key_to_atom_key(ImGuiKey key) -> keyboard_key_code
    {
        switch (key)
        {
            case ImGuiKey_None:           return keyboard_key_code::unknown;
            case ImGuiKey_Space:          return keyboard_key_code::space;
            case ImGuiKey_Apostrophe:     return keyboard_key_code::apostrophe;
            case ImGuiKey_Comma:          return keyboard_key_code::comma;
            case ImGuiKey_Minus:          return keyboard_key_code::minus;
            case ImGuiKey_Period:         return keyboard_key_code::preiod;
            case ImGuiKey_Slash:          return keyboard_key_code::slash;
            case ImGuiKey_0:              return keyboard_key_code::n0;
            case ImGuiKey_1:              return keyboard_key_code::n1;
            case ImGuiKey_2:              return keyboard_key_code::n2;
            case ImGuiKey_3:              return keyboard_key_code::n3;
            case ImGuiKey_4:              return keyboard_key_code::n4;
            case ImGuiKey_5:              return keyboard_key_code::n5;
            case ImGuiKey_6:              return keyboard_key_code::n6;
            case ImGuiKey_7:              return keyboard_key_code::n7;
            case ImGuiKey_8:              return keyboard_key_code::n8;
            case ImGuiKey_9:              return keyboard_key_code::n9;
            case ImGuiKey_Semicolon:      return keyboard_key_code::semicolon;
            case ImGuiKey_Equal:          return keyboard_key_code::equal;
            case ImGuiKey_A:              return keyboard_key_code::a;
            case ImGuiKey_B:              return keyboard_key_code::b;
            case ImGuiKey_C:              return keyboard_key_code::c;
            case ImGuiKey_D:              return keyboard_key_code::d;
            case ImGuiKey_E:              return keyboard_key_code::e;
            case ImGuiKey_F:              return keyboard_key_code::f;
            case ImGuiKey_G:              return keyboard_key_code::g;
            case ImGuiKey_H:              return keyboard_key_code::h;
            case ImGuiKey_I:              return keyboard_key_code::i;
            case ImGuiKey_J:              return keyboard_key_code::j;
            case ImGuiKey_K:              return keyboard_key_code::k;
            case ImGuiKey_L:              return keyboard_key_code::l;
            case ImGuiKey_M:              return keyboard_key_code::m;
            case ImGuiKey_N:              return keyboard_key_code::n;
            case ImGuiKey_O:              return keyboard_key_code::o;
            case ImGuiKey_P:              return keyboard_key_code::p;
            case ImGuiKey_Q:              return keyboard_key_code::q;
            case ImGuiKey_R:              return keyboard_key_code::r;
            case ImGuiKey_S:              return keyboard_key_code::s;
            case ImGuiKey_T:              return keyboard_key_code::t;
            case ImGuiKey_U:              return keyboard_key_code::u;
            case ImGuiKey_V:              return keyboard_key_code::v;
            case ImGuiKey_W:              return keyboard_key_code::w;
            case ImGuiKey_X:              return keyboard_key_code::x;
            case ImGuiKey_Y:              return keyboard_key_code::y;
            case ImGuiKey_Z:              return keyboard_key_code::z;
            case ImGuiKey_LeftBracket:    return keyboard_key_code::left_bracket;
            case ImGuiKey_Backslash:      return keyboard_key_code::backslash;
            case ImGuiKey_RightBracket:   return keyboard_key_code::right_bracket;
            case ImGuiKey_GraveAccent:    return keyboard_key_code::grave_accent;
            case ImGuiKey_Escape:         return keyboard_key_code::escape;
            case ImGuiKey_Enter:          return keyboard_key_code::enter;
            case ImGuiKey_Tab:            return keyboard_key_code::tab;
            case ImGuiKey_Backspace:      return keyboard_key_code::backspace;
            case ImGuiKey_Insert:         return keyboard_key_code::insert;
            case ImGuiKey_Delete:         return keyboard_key_code::del;
            case ImGuiKey_RightArrow:     return keyboard_key_code::right;
            case ImGuiKey_LeftArrow:      return keyboard_key_code::left;
            case ImGuiKey_DownArrow:      return keyboard_key_code::down;
            case ImGuiKey_UpArrow:        return keyboard_key_code::up;
            case ImGuiKey_PageUp:         return keyboard_key_code::page_up;
            case ImGuiKey_PageDown:       return keyboard_key_code::page_down;
            case ImGuiKey_Home:           return keyboard_key_code::home;
            case ImGuiKey_End:            return keyboard_key_code::end;
            case ImGuiKey_CapsLock:       return keyboard_key_code::caps_lock;
            case ImGuiKey_ScrollLock:     return keyboard_key_code::scroll_lock;
            case ImGuiKey_NumLock:        return keyboard_key_code::num_lock;
            case ImGuiKey_PrintScreen:    return keyboard_key_code::print_screen;
            case ImGuiKey_Pause:          return keyboard_key_code::pause;
            case ImGuiKey_F1:             return keyboard_key_code::f1;
            case ImGuiKey_F2:             return keyboard_key_code::f2;
            case ImGuiKey_F3:             return keyboard_key_code::f3;
            case ImGuiKey_F4:             return keyboard_key_code::f4;
            case ImGuiKey_F5:             return keyboard_key_code::f5;
            case ImGuiKey_F6:             return keyboard_key_code::f6;
            case ImGuiKey_F7:             return keyboard_key_code::f7;
            case ImGuiKey_F8:             return keyboard_key_code::f8;
            case ImGuiKey_F9:             return keyboard_key_code::f9;
            case ImGuiKey_F10:            return keyboard_key_code::f10;
            case ImGuiKey_F11:            return keyboard_key_code::f11;
            case ImGuiKey_F12:            return keyboard_key_code::f12;
            case ImGuiKey_F13:            return keyboard_key_code::f13;
            case ImGuiKey_F14:            return keyboard_key_code::f14;
            case ImGuiKey_F15:            return keyboard_key_code::f15;
            case ImGuiKey_F16:            return keyboard_key_code::f16;
            case ImGuiKey_F17:            return keyboard_key_code::f17;
            case ImGuiKey_F18:            return keyboard_key_code::f18;
            case ImGuiKey_F19:            return keyboard_key_code::f19;
            case ImGuiKey_F20:            return keyboard_key_code::f20;
            case ImGuiKey_F21:            return keyboard_key_code::f21;
            case ImGuiKey_F22:            return keyboard_key_code::f22;
            case ImGuiKey_F23:            return keyboard_key_code::f23;
            case ImGuiKey_F24:            return keyboard_key_code::f24;
            case ImGuiKey_Keypad0:        return keyboard_key_code::kp_0;
            case ImGuiKey_Keypad1:        return keyboard_key_code::kp_1;
            case ImGuiKey_Keypad2:        return keyboard_key_code::kp_2;
            case ImGuiKey_Keypad3:        return keyboard_key_code::kp_3;
            case ImGuiKey_Keypad4:        return keyboard_key_code::kp_4;
            case ImGuiKey_Keypad5:        return keyboard_key_code::kp_5;
            case ImGuiKey_Keypad6:        return keyboard_key_code::kp_6;
            case ImGuiKey_Keypad7:        return keyboard_key_code::kp_7;
            case ImGuiKey_Keypad8:        return keyboard_key_code::kp_8;
            case ImGuiKey_Keypad9:        return keyboard_key_code::kp_9;
            case ImGuiKey_KeypadDecimal:  return keyboard_key_code::kp_decimal;
            case ImGuiKey_KeypadDivide:   return keyboard_key_code::kp_divide;
            case ImGuiKey_KeypadMultiply: return keyboard_key_code::kp_multiply;
            case ImGuiKey_KeypadSubtract: return keyboard_key_code::kp_subtract;
            case ImGuiKey_KeypadAdd:      return keyboard_key_code::kp_add;
            case ImGuiKey_KeypadEnter:    return keyboard_key_code::kp_enter;
            case ImGuiKey_KeypadEqual:    return keyboard_key_code::kp_equal;
            case ImGuiKey_LeftShift:      return keyboard_key_code::left_shift;
            case ImGuiKey_LeftCtrl:       return keyboard_key_code::left_control;
            case ImGuiKey_LeftAlt:        return keyboard_key_code::left_alt;
            case ImGuiKey_LeftSuper:      return keyboard_key_code::left_super;
            case ImGuiKey_RightShift:     return keyboard_key_code::right_shift;
            case ImGuiKey_RightCtrl:      return keyboard_key_code::right_control;
            case ImGuiKey_RightAlt:       return keyboard_key_code::right_alt;
            case ImGuiKey_RightSuper:     return keyboard_key_code::right_super;
            case ImGuiKey_Menu:           return keyboard_key_code::menu;
            default:                      return keyboard_key_code::unknown;
        }
    }

    /// --------------------------------------------------------------------------------------------
    /// returns `ImGuiMouseButton_COUNT` if no match found.
    /// --------------------------------------------------------------------------------------------
    static auto imgui_atom_button_to_imgui_button(mouse_button_code button) -> ImGuiMouseButton_
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
    static auto imgui_imgui_button_to_atom_button(ImGuiMouseButton_ button) -> mouse_button_code
    {
        switch (button)
        {
            case ImGuiMouseButton_Left:   return mouse_button_code::left;
            case ImGuiMouseButton_Right:  return mouse_button_code::right;
            case ImGuiMouseButton_Middle: return mouse_button_code::middle;
            case ImGuiMouseButton_(3):    return mouse_button_code::n3;
            case ImGuiMouseButton_(4):    return mouse_button_code::n4;
            default:                      return mouse_button_code::unknown;
        }
    }

    /// --------------------------------------------------------------------------------------------
    /// returns `true` if `state` is `keyboard_key_state::pressed` or `keyboard_key_state::down`.
    /// --------------------------------------------------------------------------------------------
    static auto imgui_is_atom_keyboard_key_state_down(keyboard_key_state state) -> bool
    {
        if (state == keyboard_key_state::pressed || state == keyboard_key_state::down)
            return true;

        return false;
    }

    /// --------------------------------------------------------------------------------------------
    /// returns `true` if `state` is `mouse_button_state::pressed` or `mouse_button_state::down`.
    /// --------------------------------------------------------------------------------------------
    static auto imgui_is_atom_mouse_button_state_down(mouse_button_state state) -> bool
    {
        if (state == mouse_button_state::pressed || state == mouse_button_state::down)
            return true;

        return false;
    }
}
