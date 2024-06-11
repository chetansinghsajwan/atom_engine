module atom.engine:ecs.system_manager.impl;

import atom.core;
import atom.logging;
import :ecs.system_manager;

namespace atom::engine
{
    auto system_manager::initialize() -> void
    {
        _logger = logging::logger_manager::create_logger({ .name = "system_manager" })
                      .get_value_checked();
    }

    auto system_manager::finalize() -> void
    {
        delete _logger;
    }

    auto system_manager::add_system(
        class system* system) -> result<void, entry_exists_error>
    {
        _logger->log_info("adding system '{}'.", system->get_name());

        if (_systems | ranges::contains(system))
        {
            _logger->log_error("adding system failed, system already exists.");
            return entry_exists_error{ "system already exists." };
        }

        _systems.emplace_back(system);
        return result_void{};
    }

    auto system_manager::remove_system(class system* system) -> result<void, no_entry_error>
    {
        _logger->log_info("removing system '{}'", system->get_name());

        if (_systems.remove_one_find(system))
        {
            _logger->log_info("removing system done.");
            return result_void{};
        }

        _logger->log_error("removing system failed, not found.");
        return no_entry_error{ "system not found." };
    }
}
