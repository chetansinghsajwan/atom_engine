export module atom_engine:colors;

import atom_core;

namespace atom::engine
{
    export struct color
    {
        static constexpr auto from_rgb(u8 r, u8 g, u8 b) -> color
        {
            return color{ f32(r) / f32{ 255 }, f32(g) / f32{ 255 }, f32(g) / f32{ 255 }, 1 };
        }

        f32 r;
        f32 g;
        f32 b;
        f32 a;
    };

    export namespace colors
    {
        constexpr color maroon = color::from_rgb(128, 0, 0);                      // #800000
        constexpr color dark_red = color::from_rgb(139, 0, 0);                    // #8B0000
        constexpr color brown = color::from_rgb(165, 42, 42);                     // #A52A2A
        constexpr color firebrick = color::from_rgb(178, 34, 34);                 // #B22222
        constexpr color crimson = color::from_rgb(220, 20, 60);                   // #DC143C
        constexpr color red = color::from_rgb(255, 0, 0);                         // #FF0000
        constexpr color tomato = color::from_rgb(255, 99, 71);                    // #FF6347
        constexpr color coral = color::from_rgb(255, 127, 80);                    // #FF7F50
        constexpr color indian_red = color::from_rgb(205, 92, 92);                // #CD5C5C
        constexpr color light_coral = color::from_rgb(240, 128, 128);             // #F08080
        constexpr color dark_salmon = color::from_rgb(233, 150, 122);             // #E9967A
        constexpr color salmon = color::from_rgb(250, 128, 114);                  // #FA8072
        constexpr color light_salmon = color::from_rgb(255, 160, 122);            // #FFA07A
        constexpr color orange_red = color::from_rgb(255, 69, 0);                 // #FF4500
        constexpr color dark_orange = color::from_rgb(255, 140, 0);               // #FF8C00
        constexpr color orange = color::from_rgb(255, 165, 0);                    // #FFA500
        constexpr color gold = color::from_rgb(255, 215, 0);                      // #FFD700
        constexpr color dark_golden_rod = color::from_rgb(184, 134, 11);          // #B8860B
        constexpr color golden_rod = color::from_rgb(218, 165, 32);               // #DAA520
        constexpr color pale_golden_rod = color::from_rgb(238, 232, 170);         // #EEE8AA
        constexpr color dark_khaki = color::from_rgb(189, 183, 107);              // #BDB76B
        constexpr color khaki = color::from_rgb(240, 230, 140);                   // #F0E68C
        constexpr color olive = color::from_rgb(128, 128, 0);                     // #808000
        constexpr color yellow = color::from_rgb(255, 255, 0);                    // #FFFF00
        constexpr color yellow_green = color::from_rgb(154, 205, 50);             // #9ACD32
        constexpr color dark_olive_green = color::from_rgb(85, 107, 47);          // #556B2F
        constexpr color olive_drab = color::from_rgb(107, 142, 35);               // #6B8E23
        constexpr color lawn_green = color::from_rgb(124, 252, 0);                // #7CFC00
        constexpr color chartreuse = color::from_rgb(127, 255, 0);                // #7FFF00
        constexpr color green_yellow = color::from_rgb(173, 255, 47);             // #ADFF2F
        constexpr color dark_green = color::from_rgb(0, 100, 0);                  // #006400
        constexpr color green = color::from_rgb(0, 128, 0);                       // #008000
        constexpr color forest_green = color::from_rgb(34, 139, 34);              // #228B22
        constexpr color lime = color::from_rgb(0, 255, 0);                        // #00FF00
        constexpr color lime_green = color::from_rgb(50, 205, 50);                // #32CD32
        constexpr color light_green = color::from_rgb(144, 238, 144);             // #90EE90
        constexpr color pale_green = color::from_rgb(152, 251, 152);              // #98FB98
        constexpr color dark_sea_green = color::from_rgb(143, 188, 143);          // #8FBC8F
        constexpr color medium_spring_green = color::from_rgb(0, 250, 154);       // #00FA9A
        constexpr color spring_green = color::from_rgb(0, 255, 127);              // #00FF7F
        constexpr color sea_green = color::from_rgb(46, 139, 87);                 // #2E8B57
        constexpr color medium_aqua_marine = color::from_rgb(102, 205, 170);      // #66CDAA
        constexpr color medium_sea_green = color::from_rgb(60, 179, 113);         // #3CB371
        constexpr color light_sea_green = color::from_rgb(32, 178, 170);          // #20B2AA
        constexpr color dark_slate_gray = color::from_rgb(47, 79, 79);            // #2F4F4F
        constexpr color teal = color::from_rgb(0, 128, 128);                      // #008080
        constexpr color dark_cyan = color::from_rgb(0, 139, 139);                 // #008B8B
        constexpr color aqua = color::from_rgb(0, 255, 255);                      // #00FFFF
        constexpr color cyan = color::from_rgb(0, 255, 255);                      // #00FFFF
        constexpr color light_cyan = color::from_rgb(224, 255, 255);              // #E0FFFF
        constexpr color dark_turquoise = color::from_rgb(0, 206, 209);            // #00CED1
        constexpr color turquoise = color::from_rgb(64, 224, 208);                // #40E0D0
        constexpr color medium_turquoise = color::from_rgb(72, 209, 204);         // #48D1CC
        constexpr color pale_turquoise = color::from_rgb(175, 238, 238);          // #AFEEEE
        constexpr color aqua_marine = color::from_rgb(127, 255, 212);             // #7FFFD4
        constexpr color powder_blue = color::from_rgb(176, 224, 230);             // #B0E0E6
        constexpr color cadet_blue = color::from_rgb(95, 158, 160);               // #5F9EA0
        constexpr color steel_blue = color::from_rgb(70, 130, 180);               // #4682B4
        constexpr color corn_flower_blue = color::from_rgb(100, 149, 237);        // #6495ED
        constexpr color deep_sky_blue = color::from_rgb(0, 191, 255);             // #00BFFF
        constexpr color dodger_blue = color::from_rgb(30, 144, 255);              // #1E90FF
        constexpr color light_blue = color::from_rgb(173, 216, 230);              // #ADD8E6
        constexpr color sky_blue = color::from_rgb(135, 206, 235);                // #87CEEB
        constexpr color light_sky_blue = color::from_rgb(135, 206, 250);          // #87CEFA
        constexpr color midnight_blue = color::from_rgb(25, 25, 112);             // #191970
        constexpr color navy = color::from_rgb(0, 0, 128);                        // #000080
        constexpr color dark_blue = color::from_rgb(0, 0, 139);                   // #00008B
        constexpr color medium_blue = color::from_rgb(0, 0, 205);                 // #0000CD
        constexpr color blue = color::from_rgb(0, 0, 255);                        // #0000FF
        constexpr color royal_blue = color::from_rgb(65, 105, 225);               // #4169E1
        constexpr color blue_violet = color::from_rgb(138, 43, 226);              // #8A2BE2
        constexpr color indigo = color::from_rgb(75, 0, 130);                     // #4B0082
        constexpr color dark_slate_blue = color::from_rgb(72, 61, 139);           // #483D8B
        constexpr color slate_blue = color::from_rgb(106, 90, 205);               // #6A5ACD
        constexpr color medium_slate_blue = color::from_rgb(123, 104, 238);       // #7B68EE
        constexpr color medium_purple = color::from_rgb(147, 112, 219);           // #9370DB
        constexpr color dark_magenta = color::from_rgb(139, 0, 139);              // #8B008B
        constexpr color dark_violet = color::from_rgb(148, 0, 211);               // #9400D3
        constexpr color dark_orchid = color::from_rgb(153, 50, 204);              // #9932CC
        constexpr color medium_orchid = color::from_rgb(186, 85, 211);            // #BA55D3
        constexpr color purple = color::from_rgb(128, 0, 128);                    // #800080
        constexpr color thistle = color::from_rgb(216, 191, 216);                 // #D8BFD8
        constexpr color plum = color::from_rgb(221, 160, 221);                    // #DDA0DD
        constexpr color violet = color::from_rgb(238, 130, 238);                  // #EE82EE
        constexpr color magenta = color::from_rgb(255, 0, 255);                   // #FF00FF
        constexpr color orchid = color::from_rgb(218, 112, 214);                  // #DA70D6
        constexpr color medium_violet_red = color::from_rgb(199, 21, 133);        // #C71585
        constexpr color pale_violet_red = color::from_rgb(219, 112, 147);         // #DB7093
        constexpr color deep_pink = color::from_rgb(255, 20, 147);                // #FF1493
        constexpr color hot_pink = color::from_rgb(255, 105, 180);                // #FF69B4
        constexpr color light_pink = color::from_rgb(255, 182, 193);              // #FFB6C1
        constexpr color pink = color::from_rgb(255, 192, 203);                    // #FFC0CB
        constexpr color antique_white = color::from_rgb(250, 235, 215);           // #FAEBD7
        constexpr color beige = color::from_rgb(245, 245, 220);                   // #F5F5DC
        constexpr color bisque = color::from_rgb(255, 228, 196);                  // #FFE4C4
        constexpr color blanched_almond = color::from_rgb(255, 235, 205);         // #FFEBCD
        constexpr color wheat = color::from_rgb(245, 222, 179);                   // #F5DEB3
        constexpr color corn_silk = color::from_rgb(255, 248, 220);               // #FFF8DC
        constexpr color lemon_chiffon = color::from_rgb(255, 250, 205);           // #FFFACD
        constexpr color light_golden_rod_yellow = color::from_rgb(250, 250, 210); // #FAFAD2
        constexpr color light_yellow = color::from_rgb(255, 255, 224);            // #FFFFE0
        constexpr color saddle_brown = color::from_rgb(139, 69, 19);              // #8B4513
        constexpr color sienna = color::from_rgb(160, 82, 45);                    // #A0522D
        constexpr color chocolate = color::from_rgb(210, 105, 30);                // #D2691E
        constexpr color peru = color::from_rgb(205, 133, 63);                     // #CD853F
        constexpr color sandy_brown = color::from_rgb(244, 164, 96);              // #F4A460
        constexpr color burly_wood = color::from_rgb(222, 184, 135);              // #DEB887
        constexpr color tan = color::from_rgb(210, 180, 140);                     // #D2B48C
        constexpr color rosy_brown = color::from_rgb(188, 143, 143);              // #BC8F8F
        constexpr color moccasin = color::from_rgb(255, 228, 181);                // #FFE4B5
        constexpr color navajo_white = color::from_rgb(255, 222, 173);            // #FFDEAD
        constexpr color peach_puff = color::from_rgb(255, 218, 185);              // #FFDAB9
        constexpr color misty_rose = color::from_rgb(255, 228, 225);              // #FFE4E1
        constexpr color lavender_blush = color::from_rgb(255, 240, 245);          // #FFF0F5
        constexpr color linen = color::from_rgb(250, 240, 230);                   // #FAF0E6
        constexpr color old_lace = color::from_rgb(253, 245, 230);                // #FDF5E6
        constexpr color papaya_whip = color::from_rgb(255, 239, 213);             // #FFEFD5
        constexpr color sea_shell = color::from_rgb(255, 245, 238);               // #FFF5EE
        constexpr color mint_cream = color::from_rgb(245, 255, 250);              // #F5FFFA
        constexpr color slate_gray = color::from_rgb(112, 128, 144);              // #708090
        constexpr color light_slate_gray = color::from_rgb(119, 136, 153);        // #778899
        constexpr color light_steel_blue = color::from_rgb(176, 196, 222);        // #B0C4DE
        constexpr color lavender = color::from_rgb(230, 230, 250);                // #E6E6FA
        constexpr color floral_white = color::from_rgb(255, 250, 240);            // #FFFAF0
        constexpr color alice_blue = color::from_rgb(240, 248, 255);              // #F0F8FF
        constexpr color ghost_white = color::from_rgb(248, 248, 255);             // #F8F8FF
        constexpr color honeydew = color::from_rgb(240, 255, 240);                // #F0FFF0
        constexpr color ivory = color::from_rgb(255, 255, 240);                   // #FFFFF0
        constexpr color azure = color::from_rgb(240, 255, 255);                   // #F0FFFF
        constexpr color snow = color::from_rgb(255, 250, 250);                    // #FFFAFA
        constexpr color black = color::from_rgb(0, 0, 0);                         // #000000
        constexpr color dim_gray = color::from_rgb(105, 105, 105);                // #696969
        constexpr color gray = color::from_rgb(128, 128, 128);                    // #808080
        constexpr color dark_gray = color::from_rgb(169, 169, 169);               // #A9A9A9
        constexpr color silver = color::from_rgb(192, 192, 192);                  // #C0C0C0
        constexpr color light_gray = color::from_rgb(211, 211, 211);              // #D3D3D3
        constexpr color gainsboro = color::from_rgb(220, 220, 220);               // #DCDCDC
        constexpr color white_smoke = color::from_rgb(245, 245, 245);             // #F5F5F5
        constexpr color white = color::from_rgb(255, 255, 255);                   // #FFFFFF
    }
}
