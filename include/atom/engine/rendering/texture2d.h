#pragma once
#include "texture.h"

namespace atom::engine
{
    class texture2d: public texture
    {
    public:
        static auto create(string_view file_path) -> texture2d*;

    public:
        virtual auto bind(u32 slot = 0) -> void = 0;
    };
}
