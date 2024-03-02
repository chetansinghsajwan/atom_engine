#pragma once
#include "atom.core.h"
#include "atom/engine/window/window.h"
#include "atom/engine/window/window_events.h"
#include "atom/engine/window/window_manager.h"
#include "atom/engine/layers/layer.h"
#include "atom/engine/layers/layer_stack.h"

namespace atom::engine
{
    class application: public window_event_listener
    {
    public:
        application();

        virtual ~application();

    public:
        static auto get() -> application*
        {
            return _s_app;
        }

    public:
        virtual auto run() -> void;

        auto get_window() const -> window*
        {
            return _window;
        }

    private:
        virtual auto handle(window_event& event) -> void override;

    private:
        window* _window;
        layer_stack _layers;
        unique_ptr<layer> _layer;

    private:
        static inline application* _s_app;
    };
}
