#pragma once
#include "atom/engine/inputs/keyboard_events.h"
#include "atom/engine/inputs/mouse_events.h"
#include "atom/engine/layers/layer.h"
#include "atom/engine/window/window_events.h"

namespace atom::engine
{
    class imgui_layer: public layer
    {
    public:
        imgui_layer()
            : layer("imgui_layer")
            , _time(0)
        {}

    public:
        virtual auto on_attach() -> void override final;

        virtual auto on_update() -> void override final;

        virtual auto on_deattach() -> void override final;

        virtual auto handle(window_event& event) -> void override final;

        virtual auto handle(keyboard_event& event) -> void override final;

        virtual auto handle(mouse_event& event) -> void override final;

    private:
        double _time;
    };
}
