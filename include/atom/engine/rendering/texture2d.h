#pragma once
#include "texture.h"

namespace atom::engine
{
    class texture2d: public texture
    {
    public:
        static auto create(u32 width, u32 height) -> texture2d*;
        static auto create(string_view file_path) -> texture2d*;
    };
}
