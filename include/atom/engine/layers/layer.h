#pragma once
#include "atom.core.h"
#include "atom/engine/inputs/keyboard_events.h"
#include "atom/engine/inputs/mouse_events.h"
#include "atom/engine/window/window_events.h"

namespace atom::engine
{
    class layer
    {
    public:
        layer(string name)
            : _name(move(name))
        {}

        virtual ~layer() {}

    public:
        auto get_name() -> string_view
        {
            return _name;
        }

        virtual auto on_attach() -> void {}

        virtual auto on_update() -> void {}

        virtual auto on_imgui_render() -> void {}

        virtual auto on_deattach() -> void {}

    private:
        const string _name;
    };
}
