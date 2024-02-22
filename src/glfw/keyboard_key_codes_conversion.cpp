module;
#include "GLFW/glfw3.h"

export module atom.engine:glfw_keyboard_key_code_conversions;
import :keyboard_key_codes;
import atom.core;

namespace atom::engine
{
    constexpr auto convert_keyboard_key_code_atom_to_glfw(keyboard_key_code key) -> int
    {
        struct conversion_map
        {
            constexpr conversion_map()
                : map()
            {
                map[usize::unwrapped_type(keyboard_key_code::unknown)] = GLFW_KEY_UNKNOWN;
                map[usize::unwrapped_type(keyboard_key_code::space)] = GLFW_KEY_SPACE;
                map[usize::unwrapped_type(keyboard_key_code::apostrophe)] = GLFW_KEY_APOSTROPHE;
                map[usize::unwrapped_type(keyboard_key_code::comma)] = GLFW_KEY_COMMA;
                map[usize::unwrapped_type(keyboard_key_code::minus)] = GLFW_KEY_MINUS;
                map[usize::unwrapped_type(keyboard_key_code::preiod)] = GLFW_KEY_PERIOD;
                map[usize::unwrapped_type(keyboard_key_code::slash)] = GLFW_KEY_SLASH;
                map[usize::unwrapped_type(keyboard_key_code::n0)] = GLFW_KEY_0;
                map[usize::unwrapped_type(keyboard_key_code::n1)] = GLFW_KEY_1;
                map[usize::unwrapped_type(keyboard_key_code::n2)] = GLFW_KEY_2;
                map[usize::unwrapped_type(keyboard_key_code::n3)] = GLFW_KEY_3;
                map[usize::unwrapped_type(keyboard_key_code::n4)] = GLFW_KEY_4;
                map[usize::unwrapped_type(keyboard_key_code::n5)] = GLFW_KEY_5;
                map[usize::unwrapped_type(keyboard_key_code::n6)] = GLFW_KEY_6;
                map[usize::unwrapped_type(keyboard_key_code::n7)] = GLFW_KEY_7;
                map[usize::unwrapped_type(keyboard_key_code::n8)] = GLFW_KEY_8;
                map[usize::unwrapped_type(keyboard_key_code::n9)] = GLFW_KEY_9;
                map[usize::unwrapped_type(keyboard_key_code::semicolon)] = GLFW_KEY_SEMICOLON;
                map[usize::unwrapped_type(keyboard_key_code::equal)] = GLFW_KEY_EQUAL;
                map[usize::unwrapped_type(keyboard_key_code::a)] = GLFW_KEY_A;
                map[usize::unwrapped_type(keyboard_key_code::b)] = GLFW_KEY_B;
                map[usize::unwrapped_type(keyboard_key_code::c)] = GLFW_KEY_C;
                map[usize::unwrapped_type(keyboard_key_code::d)] = GLFW_KEY_D;
                map[usize::unwrapped_type(keyboard_key_code::e)] = GLFW_KEY_E;
                map[usize::unwrapped_type(keyboard_key_code::f)] = GLFW_KEY_F;
                map[usize::unwrapped_type(keyboard_key_code::g)] = GLFW_KEY_G;
                map[usize::unwrapped_type(keyboard_key_code::h)] = GLFW_KEY_H;
                map[usize::unwrapped_type(keyboard_key_code::i)] = GLFW_KEY_I;
                map[usize::unwrapped_type(keyboard_key_code::j)] = GLFW_KEY_J;
                map[usize::unwrapped_type(keyboard_key_code::k)] = GLFW_KEY_K;
                map[usize::unwrapped_type(keyboard_key_code::l)] = GLFW_KEY_L;
                map[usize::unwrapped_type(keyboard_key_code::m)] = GLFW_KEY_M;
                map[usize::unwrapped_type(keyboard_key_code::n)] = GLFW_KEY_N;
                map[usize::unwrapped_type(keyboard_key_code::o)] = GLFW_KEY_O;
                map[usize::unwrapped_type(keyboard_key_code::p)] = GLFW_KEY_P;
                map[usize::unwrapped_type(keyboard_key_code::q)] = GLFW_KEY_Q;
                map[usize::unwrapped_type(keyboard_key_code::r)] = GLFW_KEY_R;
                map[usize::unwrapped_type(keyboard_key_code::s)] = GLFW_KEY_S;
                map[usize::unwrapped_type(keyboard_key_code::t)] = GLFW_KEY_T;
                map[usize::unwrapped_type(keyboard_key_code::u)] = GLFW_KEY_U;
                map[usize::unwrapped_type(keyboard_key_code::v)] = GLFW_KEY_V;
                map[usize::unwrapped_type(keyboard_key_code::w)] = GLFW_KEY_W;
                map[usize::unwrapped_type(keyboard_key_code::x)] = GLFW_KEY_X;
                map[usize::unwrapped_type(keyboard_key_code::y)] = GLFW_KEY_Y;
                map[usize::unwrapped_type(keyboard_key_code::z)] = GLFW_KEY_Z;
                map[usize::unwrapped_type(keyboard_key_code::left_bracket)] = GLFW_KEY_LEFT_BRACKET;
                map[usize::unwrapped_type(keyboard_key_code::backslash)] = GLFW_KEY_BACKSLASH;
                map[usize::unwrapped_type(keyboard_key_code::right_bracket)] =
                    GLFW_KEY_RIGHT_BRACKET;
                map[usize::unwrapped_type(keyboard_key_code::grave_accent)] = GLFW_KEY_GRAVE_ACCENT;
                map[usize::unwrapped_type(keyboard_key_code::world_1)] = GLFW_KEY_WORLD_1;
                map[usize::unwrapped_type(keyboard_key_code::world_2)] = GLFW_KEY_WORLD_2;
                map[usize::unwrapped_type(keyboard_key_code::escape)] = GLFW_KEY_ESCAPE;
                map[usize::unwrapped_type(keyboard_key_code::enter)] = GLFW_KEY_ENTER;
                map[usize::unwrapped_type(keyboard_key_code::tab)] = GLFW_KEY_TAB;
                map[usize::unwrapped_type(keyboard_key_code::backspace)] = GLFW_KEY_BACKSPACE;
                map[usize::unwrapped_type(keyboard_key_code::insert)] = GLFW_KEY_INSERT;
                map[usize::unwrapped_type(keyboard_key_code::del)] = GLFW_KEY_DELETE;
                map[usize::unwrapped_type(keyboard_key_code::right)] = GLFW_KEY_RIGHT;
                map[usize::unwrapped_type(keyboard_key_code::left)] = GLFW_KEY_LEFT;
                map[usize::unwrapped_type(keyboard_key_code::down)] = GLFW_KEY_DOWN;
                map[usize::unwrapped_type(keyboard_key_code::up)] = GLFW_KEY_UP;
                map[usize::unwrapped_type(keyboard_key_code::page_up)] = GLFW_KEY_PAGE_UP;
                map[usize::unwrapped_type(keyboard_key_code::page_down)] = GLFW_KEY_PAGE_DOWN;
                map[usize::unwrapped_type(keyboard_key_code::home)] = GLFW_KEY_HOME;
                map[usize::unwrapped_type(keyboard_key_code::end)] = GLFW_KEY_END;
                map[usize::unwrapped_type(keyboard_key_code::caps_lock)] = GLFW_KEY_CAPS_LOCK;
                map[usize::unwrapped_type(keyboard_key_code::scroll_lock)] = GLFW_KEY_SCROLL_LOCK;
                map[usize::unwrapped_type(keyboard_key_code::num_lock)] = GLFW_KEY_NUM_LOCK;
                map[usize::unwrapped_type(keyboard_key_code::print_screen)] = GLFW_KEY_PRINT_SCREEN;
                map[usize::unwrapped_type(keyboard_key_code::pause)] = GLFW_KEY_PAUSE;
                map[usize::unwrapped_type(keyboard_key_code::f1)] = GLFW_KEY_F1;
                map[usize::unwrapped_type(keyboard_key_code::f2)] = GLFW_KEY_F2;
                map[usize::unwrapped_type(keyboard_key_code::f3)] = GLFW_KEY_F3;
                map[usize::unwrapped_type(keyboard_key_code::f4)] = GLFW_KEY_F4;
                map[usize::unwrapped_type(keyboard_key_code::f5)] = GLFW_KEY_F5;
                map[usize::unwrapped_type(keyboard_key_code::f6)] = GLFW_KEY_F6;
                map[usize::unwrapped_type(keyboard_key_code::f7)] = GLFW_KEY_F7;
                map[usize::unwrapped_type(keyboard_key_code::f8)] = GLFW_KEY_F8;
                map[usize::unwrapped_type(keyboard_key_code::f9)] = GLFW_KEY_F9;
                map[usize::unwrapped_type(keyboard_key_code::f10)] = GLFW_KEY_F10;
                map[usize::unwrapped_type(keyboard_key_code::f11)] = GLFW_KEY_F11;
                map[usize::unwrapped_type(keyboard_key_code::f12)] = GLFW_KEY_F12;
                map[usize::unwrapped_type(keyboard_key_code::f13)] = GLFW_KEY_F13;
                map[usize::unwrapped_type(keyboard_key_code::f14)] = GLFW_KEY_F14;
                map[usize::unwrapped_type(keyboard_key_code::f15)] = GLFW_KEY_F15;
                map[usize::unwrapped_type(keyboard_key_code::f16)] = GLFW_KEY_F16;
                map[usize::unwrapped_type(keyboard_key_code::f17)] = GLFW_KEY_F17;
                map[usize::unwrapped_type(keyboard_key_code::f18)] = GLFW_KEY_F18;
                map[usize::unwrapped_type(keyboard_key_code::f19)] = GLFW_KEY_F19;
                map[usize::unwrapped_type(keyboard_key_code::f20)] = GLFW_KEY_F20;
                map[usize::unwrapped_type(keyboard_key_code::f21)] = GLFW_KEY_F21;
                map[usize::unwrapped_type(keyboard_key_code::f22)] = GLFW_KEY_F22;
                map[usize::unwrapped_type(keyboard_key_code::f23)] = GLFW_KEY_F23;
                map[usize::unwrapped_type(keyboard_key_code::f24)] = GLFW_KEY_F24;
                map[usize::unwrapped_type(keyboard_key_code::f25)] = GLFW_KEY_F25;
                map[usize::unwrapped_type(keyboard_key_code::kp_0)] = GLFW_KEY_KP_0;
                map[usize::unwrapped_type(keyboard_key_code::kp_1)] = GLFW_KEY_KP_1;
                map[usize::unwrapped_type(keyboard_key_code::kp_2)] = GLFW_KEY_KP_2;
                map[usize::unwrapped_type(keyboard_key_code::kp_3)] = GLFW_KEY_KP_3;
                map[usize::unwrapped_type(keyboard_key_code::kp_4)] = GLFW_KEY_KP_4;
                map[usize::unwrapped_type(keyboard_key_code::kp_5)] = GLFW_KEY_KP_5;
                map[usize::unwrapped_type(keyboard_key_code::kp_6)] = GLFW_KEY_KP_6;
                map[usize::unwrapped_type(keyboard_key_code::kp_7)] = GLFW_KEY_KP_7;
                map[usize::unwrapped_type(keyboard_key_code::kp_8)] = GLFW_KEY_KP_8;
                map[usize::unwrapped_type(keyboard_key_code::kp_9)] = GLFW_KEY_KP_9;
                map[usize::unwrapped_type(keyboard_key_code::kp_decimal)] = GLFW_KEY_KP_DECIMAL;
                map[usize::unwrapped_type(keyboard_key_code::kp_divide)] = GLFW_KEY_KP_DIVIDE;
                map[usize::unwrapped_type(keyboard_key_code::kp_multiply)] = GLFW_KEY_KP_MULTIPLY;
                map[usize::unwrapped_type(keyboard_key_code::kp_subtract)] = GLFW_KEY_KP_SUBTRACT;
                map[usize::unwrapped_type(keyboard_key_code::kp_add)] = GLFW_KEY_KP_ADD;
                map[usize::unwrapped_type(keyboard_key_code::kp_enter)] = GLFW_KEY_KP_ENTER;
                map[usize::unwrapped_type(keyboard_key_code::kp_equal)] = GLFW_KEY_KP_EQUAL;
                map[usize::unwrapped_type(keyboard_key_code::left_shift)] = GLFW_KEY_LEFT_SHIFT;
                map[usize::unwrapped_type(keyboard_key_code::left_control)] = GLFW_KEY_LEFT_CONTROL;
                map[usize::unwrapped_type(keyboard_key_code::left_alt)] = GLFW_KEY_LEFT_ALT;
                map[usize::unwrapped_type(keyboard_key_code::left_super)] = GLFW_KEY_LEFT_SUPER;
                map[usize::unwrapped_type(keyboard_key_code::right_shift)] = GLFW_KEY_RIGHT_SHIFT;
                map[usize::unwrapped_type(keyboard_key_code::right_control)] =
                    GLFW_KEY_RIGHT_CONTROL;
                map[usize::unwrapped_type(keyboard_key_code::right_alt)] = GLFW_KEY_RIGHT_ALT;
                map[usize::unwrapped_type(keyboard_key_code::right_super)] = GLFW_KEY_RIGHT_SUPER;
                map[usize::unwrapped_type(keyboard_key_code::menu)] = GLFW_KEY_MENU;
            }

            i16::unwrapped_type map[usize::unwrapped_type(keyboard_key_code::MAX) + 1];
        };

        constexpr auto map = conversion_map();
        return map.map[usize::unwrapped_type(key)];
    }

    constexpr auto convert_keyboard_key_code_glfw_to_atom(int key) -> keyboard_key_code
    {
        struct conversion_map
        {
            consteval conversion_map()
                : map()
            {
                // map[GLFW_KEY_UNKNOWN] = keyboard_key_code::unknown;
                map[GLFW_KEY_SPACE] = keyboard_key_code::space;
                map[GLFW_KEY_APOSTROPHE] = keyboard_key_code::apostrophe;
                map[GLFW_KEY_COMMA] = keyboard_key_code::comma;
                map[GLFW_KEY_MINUS] = keyboard_key_code::minus;
                map[GLFW_KEY_PERIOD] = keyboard_key_code::preiod;
                map[GLFW_KEY_SLASH] = keyboard_key_code::slash;
                map[GLFW_KEY_0] = keyboard_key_code::n0;
                map[GLFW_KEY_1] = keyboard_key_code::n1;
                map[GLFW_KEY_2] = keyboard_key_code::n2;
                map[GLFW_KEY_3] = keyboard_key_code::n3;
                map[GLFW_KEY_4] = keyboard_key_code::n4;
                map[GLFW_KEY_5] = keyboard_key_code::n5;
                map[GLFW_KEY_6] = keyboard_key_code::n6;
                map[GLFW_KEY_7] = keyboard_key_code::n7;
                map[GLFW_KEY_8] = keyboard_key_code::n8;
                map[GLFW_KEY_9] = keyboard_key_code::n9;
                map[GLFW_KEY_SEMICOLON] = keyboard_key_code::semicolon;
                map[GLFW_KEY_EQUAL] = keyboard_key_code::equal;
                map[GLFW_KEY_A] = keyboard_key_code::a;
                map[GLFW_KEY_B] = keyboard_key_code::b;
                map[GLFW_KEY_C] = keyboard_key_code::c;
                map[GLFW_KEY_D] = keyboard_key_code::d;
                map[GLFW_KEY_E] = keyboard_key_code::e;
                map[GLFW_KEY_F] = keyboard_key_code::f;
                map[GLFW_KEY_G] = keyboard_key_code::g;
                map[GLFW_KEY_H] = keyboard_key_code::h;
                map[GLFW_KEY_I] = keyboard_key_code::i;
                map[GLFW_KEY_J] = keyboard_key_code::j;
                map[GLFW_KEY_K] = keyboard_key_code::k;
                map[GLFW_KEY_L] = keyboard_key_code::l;
                map[GLFW_KEY_M] = keyboard_key_code::m;
                map[GLFW_KEY_N] = keyboard_key_code::n;
                map[GLFW_KEY_O] = keyboard_key_code::o;
                map[GLFW_KEY_P] = keyboard_key_code::p;
                map[GLFW_KEY_Q] = keyboard_key_code::q;
                map[GLFW_KEY_R] = keyboard_key_code::r;
                map[GLFW_KEY_S] = keyboard_key_code::s;
                map[GLFW_KEY_T] = keyboard_key_code::t;
                map[GLFW_KEY_U] = keyboard_key_code::u;
                map[GLFW_KEY_V] = keyboard_key_code::v;
                map[GLFW_KEY_W] = keyboard_key_code::w;
                map[GLFW_KEY_X] = keyboard_key_code::x;
                map[GLFW_KEY_Y] = keyboard_key_code::y;
                map[GLFW_KEY_Z] = keyboard_key_code::z;
                map[GLFW_KEY_LEFT_BRACKET] = keyboard_key_code::left_bracket;
                map[GLFW_KEY_BACKSLASH] = keyboard_key_code::backslash;
                map[GLFW_KEY_RIGHT_BRACKET] = keyboard_key_code::right_bracket;
                map[GLFW_KEY_GRAVE_ACCENT] = keyboard_key_code::grave_accent;
                map[GLFW_KEY_WORLD_1] = keyboard_key_code::world_1;
                map[GLFW_KEY_WORLD_2] = keyboard_key_code::world_2;
                map[GLFW_KEY_ESCAPE] = keyboard_key_code::escape;
                map[GLFW_KEY_ENTER] = keyboard_key_code::enter;
                map[GLFW_KEY_TAB] = keyboard_key_code::tab;
                map[GLFW_KEY_BACKSPACE] = keyboard_key_code::backspace;
                map[GLFW_KEY_INSERT] = keyboard_key_code::insert;
                map[GLFW_KEY_DELETE] = keyboard_key_code::del;
                map[GLFW_KEY_RIGHT] = keyboard_key_code::right;
                map[GLFW_KEY_LEFT] = keyboard_key_code::left;
                map[GLFW_KEY_DOWN] = keyboard_key_code::down;
                map[GLFW_KEY_UP] = keyboard_key_code::up;
                map[GLFW_KEY_PAGE_UP] = keyboard_key_code::page_up;
                map[GLFW_KEY_PAGE_DOWN] = keyboard_key_code::page_down;
                map[GLFW_KEY_HOME] = keyboard_key_code::home;
                map[GLFW_KEY_END] = keyboard_key_code::end;
                map[GLFW_KEY_CAPS_LOCK] = keyboard_key_code::caps_lock;
                map[GLFW_KEY_SCROLL_LOCK] = keyboard_key_code::scroll_lock;
                map[GLFW_KEY_NUM_LOCK] = keyboard_key_code::num_lock;
                map[GLFW_KEY_PRINT_SCREEN] = keyboard_key_code::print_screen;
                map[GLFW_KEY_PAUSE] = keyboard_key_code::pause;
                map[GLFW_KEY_F1] = keyboard_key_code::f1;
                map[GLFW_KEY_F2] = keyboard_key_code::f2;
                map[GLFW_KEY_F3] = keyboard_key_code::f3;
                map[GLFW_KEY_F4] = keyboard_key_code::f4;
                map[GLFW_KEY_F5] = keyboard_key_code::f5;
                map[GLFW_KEY_F6] = keyboard_key_code::f6;
                map[GLFW_KEY_F7] = keyboard_key_code::f7;
                map[GLFW_KEY_F8] = keyboard_key_code::f8;
                map[GLFW_KEY_F9] = keyboard_key_code::f9;
                map[GLFW_KEY_F10] = keyboard_key_code::f10;
                map[GLFW_KEY_F11] = keyboard_key_code::f11;
                map[GLFW_KEY_F12] = keyboard_key_code::f12;
                map[GLFW_KEY_F13] = keyboard_key_code::f13;
                map[GLFW_KEY_F14] = keyboard_key_code::f14;
                map[GLFW_KEY_F15] = keyboard_key_code::f15;
                map[GLFW_KEY_F16] = keyboard_key_code::f16;
                map[GLFW_KEY_F17] = keyboard_key_code::f17;
                map[GLFW_KEY_F18] = keyboard_key_code::f18;
                map[GLFW_KEY_F19] = keyboard_key_code::f19;
                map[GLFW_KEY_F20] = keyboard_key_code::f20;
                map[GLFW_KEY_F21] = keyboard_key_code::f21;
                map[GLFW_KEY_F22] = keyboard_key_code::f22;
                map[GLFW_KEY_F23] = keyboard_key_code::f23;
                map[GLFW_KEY_F24] = keyboard_key_code::f24;
                map[GLFW_KEY_F25] = keyboard_key_code::f25;
                map[GLFW_KEY_KP_0] = keyboard_key_code::kp_0;
                map[GLFW_KEY_KP_1] = keyboard_key_code::kp_1;
                map[GLFW_KEY_KP_2] = keyboard_key_code::kp_2;
                map[GLFW_KEY_KP_3] = keyboard_key_code::kp_3;
                map[GLFW_KEY_KP_4] = keyboard_key_code::kp_4;
                map[GLFW_KEY_KP_5] = keyboard_key_code::kp_5;
                map[GLFW_KEY_KP_6] = keyboard_key_code::kp_6;
                map[GLFW_KEY_KP_7] = keyboard_key_code::kp_7;
                map[GLFW_KEY_KP_8] = keyboard_key_code::kp_8;
                map[GLFW_KEY_KP_9] = keyboard_key_code::kp_9;
                map[GLFW_KEY_KP_DECIMAL] = keyboard_key_code::kp_decimal;
                map[GLFW_KEY_KP_DIVIDE] = keyboard_key_code::kp_divide;
                map[GLFW_KEY_KP_MULTIPLY] = keyboard_key_code::kp_multiply;
                map[GLFW_KEY_KP_SUBTRACT] = keyboard_key_code::kp_subtract;
                map[GLFW_KEY_KP_ADD] = keyboard_key_code::kp_add;
                map[GLFW_KEY_KP_ENTER] = keyboard_key_code::kp_enter;
                map[GLFW_KEY_KP_EQUAL] = keyboard_key_code::kp_equal;
                map[GLFW_KEY_LEFT_SHIFT] = keyboard_key_code::left_shift;
                map[GLFW_KEY_LEFT_CONTROL] = keyboard_key_code::left_control;
                map[GLFW_KEY_LEFT_ALT] = keyboard_key_code::left_alt;
                map[GLFW_KEY_LEFT_SUPER] = keyboard_key_code::left_super;
                map[GLFW_KEY_RIGHT_SHIFT] = keyboard_key_code::right_shift;
                map[GLFW_KEY_RIGHT_CONTROL] = keyboard_key_code::right_control;
                map[GLFW_KEY_RIGHT_ALT] = keyboard_key_code::right_alt;
                map[GLFW_KEY_RIGHT_SUPER] = keyboard_key_code::right_super;
                map[GLFW_KEY_MENU] = keyboard_key_code::menu;
            }

            keyboard_key_code map[GLFW_KEY_LAST + 1];
        };

        contracts::debug_expects(key >= -1 || key <= GLFW_KEY_MENU, "glfw key is out of range.");

        if (key == GLFW_KEY_UNKNOWN)
            return keyboard_key_code::unknown;

        constexpr auto map = conversion_map();
        return map.map[key];
    }

    constexpr auto convert_keyboard_key_state_atom_to_glfw(keyboard_key_state state) -> int
    {
        struct conversion_map
        {
            consteval conversion_map()
            {
                map[usize::unwrapped_type(keyboard_key_state::up)] = GLFW_RELEASE;
                map[usize::unwrapped_type(keyboard_key_state::pressed)] = GLFW_PRESS;
                map[usize::unwrapped_type(keyboard_key_state::down)] = GLFW_PRESS;
                map[usize::unwrapped_type(keyboard_key_state::released)] = GLFW_RELEASE;
            }

            int map[usize::unwrapped_type(keyboard_key_state::MAX) + 1];
        };

        constexpr auto map = conversion_map();
        return map.map[usize::unwrapped_type(state)];
    }

    constexpr auto convert_keyboard_key_state_glfw_to_atom(int state) -> keyboard_key_state
    {
        struct conversion_map
        {
            consteval conversion_map()
            {
                map[GLFW_PRESS] = keyboard_key_state::pressed;
                map[GLFW_RELEASE] = keyboard_key_state::released;
            }

            keyboard_key_state map[2];
        };

        contracts::debug_expects(state <= GLFW_PRESS, "glfw state is out of range.");

        constexpr auto map = conversion_map();
        return map.map[state];
    }
}
