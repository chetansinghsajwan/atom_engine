#pragma once
#include "atom.core.h"
#include "atom/core/memory/unique_ptr.h"
#include "atom/engine/rendering/shader.h"
#include "atom/engine/window/window.h"
#include "atom/engine/window/window_events.h"
#include "atom/engine/layers/layer.h"
#include "atom/engine/layers/layer_stack.h"
#include "atom/engine/time.h"

namespace atom::engine
{
    class application
        : public window_event_listener
        , public keyboard_event_listener
        , public mouse_event_listener
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

        auto push_layer(class layer* layer) -> void
        {
            _layers.push_layer(layer);
        }

    private:
        virtual auto handle(window_event& event) -> void override;

        auto _on_window_resize_event(window_resize_event& event) -> void;

        virtual auto handle(keyboard_event& event) -> void override;

        virtual auto handle(mouse_event& event) -> void override;

    private:
        window* _window;
        layer_stack _layers;
        layer* _layer;
        float _last_frame_time;
        bool _should_run;

    private:
        static inline application* _s_app;
    };
}
