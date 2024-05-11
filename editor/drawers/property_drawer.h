#pragma once
#include "imgui.h"

namespace atom::editor
{
    class property_drawer
    {
    public:
        property_drawer() {}

    public:
        virtual auto draw() -> void = 0;

        virtual auto get_heading() -> string_view = 0;
    };
}
