#pragma once
#include "atom/engine/inputs/keyboard_keys.h"

#include "GLFW/glfw3.h"

/// ------------------------------------------------------------------------------------------------
/// @todo maybe convert panics to debug panics, return unknown values in release.
/// ------------------------------------------------------------------------------------------------
namespace atom::engine
{
    constexpr auto convert_keyboard_key_code_atom_to_glfw(keyboard_key_code key) -> int
    {
        switch (key)
        {
            case keyboard_key_code::unknown:       return GLFW_KEY_UNKNOWN;
            case keyboard_key_code::space:         return GLFW_KEY_SPACE;
            case keyboard_key_code::apostrophe:    return GLFW_KEY_APOSTROPHE;
            case keyboard_key_code::comma:         return GLFW_KEY_COMMA;
            case keyboard_key_code::minus:         return GLFW_KEY_MINUS;
            case keyboard_key_code::preiod:        return GLFW_KEY_PERIOD;
            case keyboard_key_code::slash:         return GLFW_KEY_SLASH;
            case keyboard_key_code::n0:            return GLFW_KEY_0;
            case keyboard_key_code::n1:            return GLFW_KEY_1;
            case keyboard_key_code::n2:            return GLFW_KEY_2;
            case keyboard_key_code::n3:            return GLFW_KEY_3;
            case keyboard_key_code::n4:            return GLFW_KEY_4;
            case keyboard_key_code::n5:            return GLFW_KEY_5;
            case keyboard_key_code::n6:            return GLFW_KEY_6;
            case keyboard_key_code::n7:            return GLFW_KEY_7;
            case keyboard_key_code::n8:            return GLFW_KEY_8;
            case keyboard_key_code::n9:            return GLFW_KEY_9;
            case keyboard_key_code::semicolon:     return GLFW_KEY_SEMICOLON;
            case keyboard_key_code::equal:         return GLFW_KEY_EQUAL;
            case keyboard_key_code::a:             return GLFW_KEY_A;
            case keyboard_key_code::b:             return GLFW_KEY_B;
            case keyboard_key_code::c:             return GLFW_KEY_C;
            case keyboard_key_code::d:             return GLFW_KEY_D;
            case keyboard_key_code::e:             return GLFW_KEY_E;
            case keyboard_key_code::f:             return GLFW_KEY_F;
            case keyboard_key_code::g:             return GLFW_KEY_G;
            case keyboard_key_code::h:             return GLFW_KEY_H;
            case keyboard_key_code::i:             return GLFW_KEY_I;
            case keyboard_key_code::j:             return GLFW_KEY_J;
            case keyboard_key_code::k:             return GLFW_KEY_K;
            case keyboard_key_code::l:             return GLFW_KEY_L;
            case keyboard_key_code::m:             return GLFW_KEY_M;
            case keyboard_key_code::n:             return GLFW_KEY_N;
            case keyboard_key_code::o:             return GLFW_KEY_O;
            case keyboard_key_code::p:             return GLFW_KEY_P;
            case keyboard_key_code::q:             return GLFW_KEY_Q;
            case keyboard_key_code::r:             return GLFW_KEY_R;
            case keyboard_key_code::s:             return GLFW_KEY_S;
            case keyboard_key_code::t:             return GLFW_KEY_T;
            case keyboard_key_code::u:             return GLFW_KEY_U;
            case keyboard_key_code::v:             return GLFW_KEY_V;
            case keyboard_key_code::w:             return GLFW_KEY_W;
            case keyboard_key_code::x:             return GLFW_KEY_X;
            case keyboard_key_code::y:             return GLFW_KEY_Y;
            case keyboard_key_code::z:             return GLFW_KEY_Z;
            case keyboard_key_code::left_bracket:  return GLFW_KEY_LEFT_BRACKET;
            case keyboard_key_code::backslash:     return GLFW_KEY_BACKSLASH;
            case keyboard_key_code::right_bracket: return GLFW_KEY_RIGHT_BRACKET;
            case keyboard_key_code::grave_accent:  return GLFW_KEY_GRAVE_ACCENT;
            case keyboard_key_code::world_1:       return GLFW_KEY_WORLD_1;
            case keyboard_key_code::world_2:       return GLFW_KEY_WORLD_2;
            case keyboard_key_code::escape:        return GLFW_KEY_ESCAPE;
            case keyboard_key_code::enter:         return GLFW_KEY_ENTER;
            case keyboard_key_code::tab:           return GLFW_KEY_TAB;
            case keyboard_key_code::backspace:     return GLFW_KEY_BACKSPACE;
            case keyboard_key_code::insert:        return GLFW_KEY_INSERT;
            case keyboard_key_code::del:           return GLFW_KEY_DELETE;
            case keyboard_key_code::right:         return GLFW_KEY_RIGHT;
            case keyboard_key_code::left:          return GLFW_KEY_LEFT;
            case keyboard_key_code::down:          return GLFW_KEY_DOWN;
            case keyboard_key_code::up:            return GLFW_KEY_UP;
            case keyboard_key_code::page_up:       return GLFW_KEY_PAGE_UP;
            case keyboard_key_code::page_down:     return GLFW_KEY_PAGE_DOWN;
            case keyboard_key_code::home:          return GLFW_KEY_HOME;
            case keyboard_key_code::end:           return GLFW_KEY_END;
            case keyboard_key_code::caps_lock:     return GLFW_KEY_CAPS_LOCK;
            case keyboard_key_code::scroll_lock:   return GLFW_KEY_SCROLL_LOCK;
            case keyboard_key_code::num_lock:      return GLFW_KEY_NUM_LOCK;
            case keyboard_key_code::print_screen:  return GLFW_KEY_PRINT_SCREEN;
            case keyboard_key_code::pause:         return GLFW_KEY_PAUSE;
            case keyboard_key_code::f1:            return GLFW_KEY_F1;
            case keyboard_key_code::f2:            return GLFW_KEY_F2;
            case keyboard_key_code::f3:            return GLFW_KEY_F3;
            case keyboard_key_code::f4:            return GLFW_KEY_F4;
            case keyboard_key_code::f5:            return GLFW_KEY_F5;
            case keyboard_key_code::f6:            return GLFW_KEY_F6;
            case keyboard_key_code::f7:            return GLFW_KEY_F7;
            case keyboard_key_code::f8:            return GLFW_KEY_F8;
            case keyboard_key_code::f9:            return GLFW_KEY_F9;
            case keyboard_key_code::f10:           return GLFW_KEY_F10;
            case keyboard_key_code::f11:           return GLFW_KEY_F11;
            case keyboard_key_code::f12:           return GLFW_KEY_F12;
            case keyboard_key_code::f13:           return GLFW_KEY_F13;
            case keyboard_key_code::f14:           return GLFW_KEY_F14;
            case keyboard_key_code::f15:           return GLFW_KEY_F15;
            case keyboard_key_code::f16:           return GLFW_KEY_F16;
            case keyboard_key_code::f17:           return GLFW_KEY_F17;
            case keyboard_key_code::f18:           return GLFW_KEY_F18;
            case keyboard_key_code::f19:           return GLFW_KEY_F19;
            case keyboard_key_code::f20:           return GLFW_KEY_F20;
            case keyboard_key_code::f21:           return GLFW_KEY_F21;
            case keyboard_key_code::f22:           return GLFW_KEY_F22;
            case keyboard_key_code::f23:           return GLFW_KEY_F23;
            case keyboard_key_code::f24:           return GLFW_KEY_F24;
            case keyboard_key_code::f25:           return GLFW_KEY_F25;
            case keyboard_key_code::kp_0:          return GLFW_KEY_KP_0;
            case keyboard_key_code::kp_1:          return GLFW_KEY_KP_1;
            case keyboard_key_code::kp_2:          return GLFW_KEY_KP_2;
            case keyboard_key_code::kp_3:          return GLFW_KEY_KP_3;
            case keyboard_key_code::kp_4:          return GLFW_KEY_KP_4;
            case keyboard_key_code::kp_5:          return GLFW_KEY_KP_5;
            case keyboard_key_code::kp_6:          return GLFW_KEY_KP_6;
            case keyboard_key_code::kp_7:          return GLFW_KEY_KP_7;
            case keyboard_key_code::kp_8:          return GLFW_KEY_KP_8;
            case keyboard_key_code::kp_9:          return GLFW_KEY_KP_9;
            case keyboard_key_code::kp_decimal:    return GLFW_KEY_KP_DECIMAL;
            case keyboard_key_code::kp_divide:     return GLFW_KEY_KP_DIVIDE;
            case keyboard_key_code::kp_multiply:   return GLFW_KEY_KP_MULTIPLY;
            case keyboard_key_code::kp_subtract:   return GLFW_KEY_KP_SUBTRACT;
            case keyboard_key_code::kp_add:        return GLFW_KEY_KP_ADD;
            case keyboard_key_code::kp_enter:      return GLFW_KEY_KP_ENTER;
            case keyboard_key_code::kp_equal:      return GLFW_KEY_KP_EQUAL;
            case keyboard_key_code::left_shift:    return GLFW_KEY_LEFT_SHIFT;
            case keyboard_key_code::left_control:  return GLFW_KEY_LEFT_CONTROL;
            case keyboard_key_code::left_alt:      return GLFW_KEY_LEFT_ALT;
            case keyboard_key_code::left_super:    return GLFW_KEY_LEFT_SUPER;
            case keyboard_key_code::right_shift:   return GLFW_KEY_RIGHT_SHIFT;
            case keyboard_key_code::right_control: return GLFW_KEY_RIGHT_CONTROL;
            case keyboard_key_code::right_alt:     return GLFW_KEY_RIGHT_ALT;
            case keyboard_key_code::right_super:   return GLFW_KEY_RIGHT_SUPER;
            case keyboard_key_code::menu:          return GLFW_KEY_MENU;
            default:
            {
                ATOM_PANIC("invalid key.", key);
            }
        }
    }

    constexpr auto convert_keyboard_key_code_glfw_to_atom(int key) -> keyboard_key_code
    {
        switch (key)
        {
            case GLFW_KEY_UNKNOWN:       return keyboard_key_code::unknown;
            case GLFW_KEY_SPACE:         return keyboard_key_code::space;
            case GLFW_KEY_APOSTROPHE:    return keyboard_key_code::apostrophe;
            case GLFW_KEY_COMMA:         return keyboard_key_code::comma;
            case GLFW_KEY_MINUS:         return keyboard_key_code::minus;
            case GLFW_KEY_PERIOD:        return keyboard_key_code::preiod;
            case GLFW_KEY_SLASH:         return keyboard_key_code::slash;
            case GLFW_KEY_0:             return keyboard_key_code::n0;
            case GLFW_KEY_1:             return keyboard_key_code::n1;
            case GLFW_KEY_2:             return keyboard_key_code::n2;
            case GLFW_KEY_3:             return keyboard_key_code::n3;
            case GLFW_KEY_4:             return keyboard_key_code::n4;
            case GLFW_KEY_5:             return keyboard_key_code::n5;
            case GLFW_KEY_6:             return keyboard_key_code::n6;
            case GLFW_KEY_7:             return keyboard_key_code::n7;
            case GLFW_KEY_8:             return keyboard_key_code::n8;
            case GLFW_KEY_9:             return keyboard_key_code::n9;
            case GLFW_KEY_SEMICOLON:     return keyboard_key_code::semicolon;
            case GLFW_KEY_EQUAL:         return keyboard_key_code::equal;
            case GLFW_KEY_A:             return keyboard_key_code::a;
            case GLFW_KEY_B:             return keyboard_key_code::b;
            case GLFW_KEY_C:             return keyboard_key_code::c;
            case GLFW_KEY_D:             return keyboard_key_code::d;
            case GLFW_KEY_E:             return keyboard_key_code::e;
            case GLFW_KEY_F:             return keyboard_key_code::f;
            case GLFW_KEY_G:             return keyboard_key_code::g;
            case GLFW_KEY_H:             return keyboard_key_code::h;
            case GLFW_KEY_I:             return keyboard_key_code::i;
            case GLFW_KEY_J:             return keyboard_key_code::j;
            case GLFW_KEY_K:             return keyboard_key_code::k;
            case GLFW_KEY_L:             return keyboard_key_code::l;
            case GLFW_KEY_M:             return keyboard_key_code::m;
            case GLFW_KEY_N:             return keyboard_key_code::n;
            case GLFW_KEY_O:             return keyboard_key_code::o;
            case GLFW_KEY_P:             return keyboard_key_code::p;
            case GLFW_KEY_Q:             return keyboard_key_code::q;
            case GLFW_KEY_R:             return keyboard_key_code::r;
            case GLFW_KEY_S:             return keyboard_key_code::s;
            case GLFW_KEY_T:             return keyboard_key_code::t;
            case GLFW_KEY_U:             return keyboard_key_code::u;
            case GLFW_KEY_V:             return keyboard_key_code::v;
            case GLFW_KEY_W:             return keyboard_key_code::w;
            case GLFW_KEY_X:             return keyboard_key_code::x;
            case GLFW_KEY_Y:             return keyboard_key_code::y;
            case GLFW_KEY_Z:             return keyboard_key_code::z;
            case GLFW_KEY_LEFT_BRACKET:  return keyboard_key_code::left_bracket;
            case GLFW_KEY_BACKSLASH:     return keyboard_key_code::backslash;
            case GLFW_KEY_RIGHT_BRACKET: return keyboard_key_code::right_bracket;
            case GLFW_KEY_GRAVE_ACCENT:  return keyboard_key_code::grave_accent;
            case GLFW_KEY_WORLD_1:       return keyboard_key_code::world_1;
            case GLFW_KEY_WORLD_2:       return keyboard_key_code::world_2;
            case GLFW_KEY_ESCAPE:        return keyboard_key_code::escape;
            case GLFW_KEY_ENTER:         return keyboard_key_code::enter;
            case GLFW_KEY_TAB:           return keyboard_key_code::tab;
            case GLFW_KEY_BACKSPACE:     return keyboard_key_code::backspace;
            case GLFW_KEY_INSERT:        return keyboard_key_code::insert;
            case GLFW_KEY_DELETE:        return keyboard_key_code::del;
            case GLFW_KEY_RIGHT:         return keyboard_key_code::right;
            case GLFW_KEY_LEFT:          return keyboard_key_code::left;
            case GLFW_KEY_DOWN:          return keyboard_key_code::down;
            case GLFW_KEY_UP:            return keyboard_key_code::up;
            case GLFW_KEY_PAGE_UP:       return keyboard_key_code::page_up;
            case GLFW_KEY_PAGE_DOWN:     return keyboard_key_code::page_down;
            case GLFW_KEY_HOME:          return keyboard_key_code::home;
            case GLFW_KEY_END:           return keyboard_key_code::end;
            case GLFW_KEY_CAPS_LOCK:     return keyboard_key_code::caps_lock;
            case GLFW_KEY_SCROLL_LOCK:   return keyboard_key_code::scroll_lock;
            case GLFW_KEY_NUM_LOCK:      return keyboard_key_code::num_lock;
            case GLFW_KEY_PRINT_SCREEN:  return keyboard_key_code::print_screen;
            case GLFW_KEY_PAUSE:         return keyboard_key_code::pause;
            case GLFW_KEY_F1:            return keyboard_key_code::f1;
            case GLFW_KEY_F2:            return keyboard_key_code::f2;
            case GLFW_KEY_F3:            return keyboard_key_code::f3;
            case GLFW_KEY_F4:            return keyboard_key_code::f4;
            case GLFW_KEY_F5:            return keyboard_key_code::f5;
            case GLFW_KEY_F6:            return keyboard_key_code::f6;
            case GLFW_KEY_F7:            return keyboard_key_code::f7;
            case GLFW_KEY_F8:            return keyboard_key_code::f8;
            case GLFW_KEY_F9:            return keyboard_key_code::f9;
            case GLFW_KEY_F10:           return keyboard_key_code::f10;
            case GLFW_KEY_F11:           return keyboard_key_code::f11;
            case GLFW_KEY_F12:           return keyboard_key_code::f12;
            case GLFW_KEY_F13:           return keyboard_key_code::f13;
            case GLFW_KEY_F14:           return keyboard_key_code::f14;
            case GLFW_KEY_F15:           return keyboard_key_code::f15;
            case GLFW_KEY_F16:           return keyboard_key_code::f16;
            case GLFW_KEY_F17:           return keyboard_key_code::f17;
            case GLFW_KEY_F18:           return keyboard_key_code::f18;
            case GLFW_KEY_F19:           return keyboard_key_code::f19;
            case GLFW_KEY_F20:           return keyboard_key_code::f20;
            case GLFW_KEY_F21:           return keyboard_key_code::f21;
            case GLFW_KEY_F22:           return keyboard_key_code::f22;
            case GLFW_KEY_F23:           return keyboard_key_code::f23;
            case GLFW_KEY_F24:           return keyboard_key_code::f24;
            case GLFW_KEY_F25:           return keyboard_key_code::f25;
            case GLFW_KEY_KP_0:          return keyboard_key_code::kp_0;
            case GLFW_KEY_KP_1:          return keyboard_key_code::kp_1;
            case GLFW_KEY_KP_2:          return keyboard_key_code::kp_2;
            case GLFW_KEY_KP_3:          return keyboard_key_code::kp_3;
            case GLFW_KEY_KP_4:          return keyboard_key_code::kp_4;
            case GLFW_KEY_KP_5:          return keyboard_key_code::kp_5;
            case GLFW_KEY_KP_6:          return keyboard_key_code::kp_6;
            case GLFW_KEY_KP_7:          return keyboard_key_code::kp_7;
            case GLFW_KEY_KP_8:          return keyboard_key_code::kp_8;
            case GLFW_KEY_KP_9:          return keyboard_key_code::kp_9;
            case GLFW_KEY_KP_DECIMAL:    return keyboard_key_code::kp_decimal;
            case GLFW_KEY_KP_DIVIDE:     return keyboard_key_code::kp_divide;
            case GLFW_KEY_KP_MULTIPLY:   return keyboard_key_code::kp_multiply;
            case GLFW_KEY_KP_SUBTRACT:   return keyboard_key_code::kp_subtract;
            case GLFW_KEY_KP_ADD:        return keyboard_key_code::kp_add;
            case GLFW_KEY_KP_ENTER:      return keyboard_key_code::kp_enter;
            case GLFW_KEY_KP_EQUAL:      return keyboard_key_code::kp_equal;
            case GLFW_KEY_LEFT_SHIFT:    return keyboard_key_code::left_shift;
            case GLFW_KEY_LEFT_CONTROL:  return keyboard_key_code::left_control;
            case GLFW_KEY_LEFT_ALT:      return keyboard_key_code::left_alt;
            case GLFW_KEY_LEFT_SUPER:    return keyboard_key_code::left_super;
            case GLFW_KEY_RIGHT_SHIFT:   return keyboard_key_code::right_shift;
            case GLFW_KEY_RIGHT_CONTROL: return keyboard_key_code::right_control;
            case GLFW_KEY_RIGHT_ALT:     return keyboard_key_code::right_alt;
            case GLFW_KEY_RIGHT_SUPER:   return keyboard_key_code::right_super;
            case GLFW_KEY_MENU:          return keyboard_key_code::menu;
            default:
            {
                ATOM_PANIC("invalid key.", key);
            }
        }
    }

    constexpr auto convert_keyboard_key_state_atom_to_glfw(keyboard_key_state state) -> int
    {
        switch (state)
        {
            case keyboard_key_state::up:       return GLFW_RELEASE;
            case keyboard_key_state::pressed:  return GLFW_PRESS;
            case keyboard_key_state::down:     return GLFW_PRESS;
            case keyboard_key_state::released: return GLFW_RELEASE;
            default:
            {
                ATOM_PANIC("invalid state.", state);
            }
        }
    }

    constexpr auto convert_keyboard_key_state_glfw_to_atom(int state) -> keyboard_key_state
    {
        switch (state)
        {
            case GLFW_PRESS:   return keyboard_key_state::pressed;
            case GLFW_RELEASE: return keyboard_key_state::released;
            default:
            {
                ATOM_PANIC("invalid state.", state);
            }
        }
    }
}
