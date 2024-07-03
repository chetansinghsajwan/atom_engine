export module atom_engine:ecs.system;

import atom_core;
import :time;

namespace atom::engine
{
    export class world;

    export class system
    {
    public:
        system(string name, class world* world);
        ~system();

    public:
        auto get_name() const -> string_view;

        auto get_world() -> world*;

        virtual auto on_initialize() -> void;

        virtual auto on_finalize() -> void;

        virtual auto on_start() -> void;

        virtual auto on_stop() -> void;

        virtual auto on_update(time_step time) -> void;

    private:
        string _name;
        world* _world;
    };
}
