module;
#include "GLFW/glfw3.h"

module atom.engine:application.impl;

import atom.core;
import :application;
import :imgui;
import :time;

namespace atom::engine
{
    auto application::_setup_layer() -> void
    {
        _layer = new imgui_layer();
        _layers.push_layer(_layer);
    }

    auto application::_run() -> void
    {
        while (_should_run)
        {
            f32 time = glfwGetTime();
            f32 delta_time = time - _last_frame_time;
            _last_frame_time = time;

            if (!_window->is_minimized())
            {
                for (layer* layer : _layers.get_layers())
                    layer->on_update(time_step(delta_time));
            }

            class imgui_layer* imgui_layer = (class imgui_layer*)_layer;

            imgui_layer->begin_render();
            for (layer* layer : _layers.get_layers())
            {
                layer->on_imgui_render();
            }
            imgui_layer->end_render();

            _window->update();
        }
    }
}
