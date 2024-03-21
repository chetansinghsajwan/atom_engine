#pragma once
#include "atom.core.h"
#include "atom/core/memory/unique_ptr.h"
#include "atom/engine/rendering/shader.h"
#include "atom/engine/window/window.h"
#include "atom/engine/window/window_events.h"
#include "atom/engine/layers/layer.h"
#include "atom/engine/layers/layer_stack.h"
#include "engine/rendering/vertex_array.h"
#include "engine/rendering/vertex_buffer.h"
#include "engine/rendering/index_buffer.h"

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

    private:
        virtual auto handle(window_event& event) -> void override;

        virtual auto handle(keyboard_event& event) -> void override;

        virtual auto handle(mouse_event& event) -> void override;

    private:
        window* _window;
        layer_stack _layers;
        layer* _layer;
        std::unique_ptr<shader> _shader;
        std::unique_ptr<vertex_array> _vertex_array;
        bool _should_run;

    private:
        static inline application* _s_app;
    };
}
