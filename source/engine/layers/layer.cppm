export module atom.engine:layers.layer;

import atom.core;
import :windows;
import :inputs;
import :time;

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

        virtual auto on_update(time_step delta_time) -> void {}

        virtual auto on_imgui_render() -> void {}

        virtual auto on_deattach() -> void {}

    private:
        const string _name;
    };
}
