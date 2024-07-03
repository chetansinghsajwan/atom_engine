export module atom_engine:layers.layer_stack;

import atom_core;
import :time;
import :windows;
import :layers.layer;

namespace atom::engine
{
    export class layer_stack
    {
    public:
        layer_stack()
            : _layers()
            , _normal_layer_count(0)
        {}

    public:
        auto push_layer(layer* layer) -> void
        {
            contract_debug_expects(layer != nullptr);

            _layers.emplace_at(_normal_layer_count, layer);
            _normal_layer_count++;
            layer->on_attach();
        }

        auto pop_layer(layer* layer) -> void
        {
            contract_debug_expects(layer != nullptr);

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
            contract_debug_expects(layer != nullptr);

            _layers.emplace_back(layer);
            layer->on_attach();
        }

        auto pop_overlay_layer(layer* layer) -> void
        {
            contract_debug_expects(layer != nullptr);

            if (_layers.remove_one_find(layer))
            {
                layer->on_deattach();
            }
        }

        auto count_overlay_layers() const -> usize
        {
            return _layers.get_count() - _normal_layer_count;
        }

        auto update_layers(time_step delta_time)
        {
            for (layer* layer : _layers)
            {
                layer->on_update(delta_time);
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
