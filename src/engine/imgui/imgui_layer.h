#pragma once
#include "atom/engine/layers/layer.h"

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
        virtual auto on_attach() -> void override;

        virtual auto on_imgui_render() -> void override;

        virtual auto on_deattach() -> void override;

        auto begin_render() -> void;

        auto end_render() -> void;

    private:
        double _time;
    };
}
