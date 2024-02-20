export module atom.engine:layer_stack;
import :window;
import atom.core;

namespace atom::engine
{
    /// --------------------------------------------------------------------------------------------
    ///
    /// --------------------------------------------------------------------------------------------
    export class layer
    {
    public:
        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        layer(string name)
            : _name(move(name))
        {}

        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        virtual ~layer() {}

    public:
        /// ----------------------------------------------------------------------------------------
        /// maybe we will keep this only for debug.
        /// ----------------------------------------------------------------------------------------
        auto get_name() -> string_view
        {
            return _name;
        }

        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        virtual auto on_attach() -> void {}

        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        virtual auto on_deattach() -> void {}

        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        virtual auto on_update() -> void {}

        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        virtual auto on_window_event(window_event& event) -> void {}

    private:
        const string _name;
    };

    export class layer_stack
    {
    public:
        layer_stack()
            : _layers()
            , _normal_layer_count(0)
        {}

    public:
        auto push_layer(mut_ptr<layer> layer) -> void
        {
            contracts::debug_expects(layer != nullptr);

            _layers.emplace_at(_normal_layer_count, layer);
            _normal_layer_count++;
        }

        auto pop_layer(mut_ptr<layer> layer) -> void
        {
            contracts::debug_expects(layer != nullptr);

            _layers.remove_find(layer);
        }

        auto count_layers() const -> usize
        {
            return _normal_layer_count;
        }

        auto push_overlay_layer(mut_ptr<layer> layer) -> void
        {
            contracts::debug_expects(layer != nullptr);

            _layers.emplace_back(layer);
        }

        auto pop_overlay_layer(mut_ptr<layer> layer) -> void
        {
            contracts::debug_expects(layer != nullptr);

            _layers.remove_find(layer);
        }

        auto count_overlay_layers() const -> usize
        {
            return _layers.count() - _normal_layer_count;
        }

    private:
        dynamic_array<mut_ptr<layer>> _layers;
        usize _normal_layer_count;
    };
}