#pragma once
#include "texture.h"

namespace atom::engine
{
    class texture2d: public texture
    {
    public:
        static auto create(string_view file_path) -> texture2d*;
    };
}
