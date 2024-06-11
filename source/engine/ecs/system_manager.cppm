export module atom.engine:ecs.system_manager;

import atom.core;
import atom.logging;
import :ecs.system;

namespace atom::engine
{
    export class system_manager
    {
    public:
        static auto initialize() -> void;

        static auto finalize() -> void;

        static auto add_system(class system* system) -> result<void, entry_exists_error>;

        static auto remove_system(class system* system) -> result<void, no_entry_error>;

    private:
        static dynamic_array<system*> _systems;
        static logging::logger* _logger;
    };
}
