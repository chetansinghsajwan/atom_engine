export module atom.engine:ecs.system;

import atom.core;
import :time;

namespace atom::engine
{
    export class system
    {
    public:
        system(string name);
        ~system();

    public:
        auto get_name() const -> string_view;

        virtual auto on_start() -> void;
        virtual auto on_update(time_step time) -> void;
        virtual auto on_stop() -> void;

    private:
        string _name;
    };
}
