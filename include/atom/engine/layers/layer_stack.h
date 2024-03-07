#pragma once
#include "atom.core.h"
#include "atom/engine/layers/layer.h"
#include "atom/engine/window/window_events.h"

namespace atom::engine
{
    class layer_stack
    {
    public:
        layer_stack()
            : _layers()
            , _normal_layer_count(0)
        {}

    public:
        auto push_layer(layer* layer) -> void
        {
            ATOM_DEBUG_EXPECTS(layer != nullptr);

            _layers.emplace_at(_normal_layer_count, layer);
            _normal_layer_count++;
            layer->on_attach();
        }

        auto pop_layer(layer* layer) -> void
        {
            ATOM_DEBUG_EXPECTS(layer != nullptr);

            if (_layers.remove_one_find(layer))
            {
                layer->on_deattach();
            }
        }

        auto count_layers() const -> usize
        {
            return _normal_layer_count;
        }

        auto push_overlay_layer(layer* layer) -> void
        {
            ATOM_DEBUG_EXPECTS(layer != nullptr);

            _layers.emplace_back(layer);
            layer->on_attach();
        }

        auto pop_overlay_layer(layer* layer) -> void
        {
            ATOM_DEBUG_EXPECTS(layer != nullptr);

            if (_layers.remove_one_find(layer))
            {
                layer->on_deattach();
            }
        }

        auto count_overlay_layers() const -> usize
        {
            return _layers.get_count() - _normal_layer_count;
        }

        auto update_layers()
        {
            for (layer* layer : _layers)
            {
                layer->on_update();
            }
        }

        auto get_layers() const -> array_view<layer*>
        {
            return _layers;
        }

    private:
        dynamic_array<layer*> _layers;
        usize _normal_layer_count;
    };
}
