export module atom.engine:ecs.system_manager;

import atom.core;
import atom.logging;
import :ecs.system;
import :time;

namespace atom::engine
{
    export class system_manager
    {
    public:
        auto initialize() -> void;

        auto finalize() -> void;

        auto add_system(class system* system) -> result<void, entry_exists_error>;

        auto remove_system(class system* system) -> result<void, no_entry_error>;

        auto update_systems(time_step time) -> void;

    private:
        dynamic_array<system*> _systems;
        logging::logger* _logger;
    };
}
