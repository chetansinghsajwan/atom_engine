module atom_engine:ecs.system_manager.impl;

import atom_core;
import atom_logging;
import :time;
import :ecs.system_manager;
import :ecs.system;

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

    auto system_manager::add_system(type_id id, system* system) -> result<void, entry_exists_error>
    {
        _logger->log_info("adding system '{}' with id '{}'...", system->get_name(), id);

        if (_has_system(id))
        {
            _logger->log_error("adding system failed, system already exists.");
            return entry_exists_error{ "system already exists." };
        }

        _systems.emplace_back(id, system);
        _logger->log_info("adding system done.");

        system->on_initialize();

        return { create_from_void };
    }

    auto system_manager::remove_system(type_id id) -> result<void, no_entry_error>
    {
        _logger->log_info("removing system with id '{}", id);

        bool removed = _systems.remove_one_if([&](const auto& entry) { return entry.first == id; });
        if (not removed)
        {
            _logger->log_error("removing system failed, not found.");
            return no_entry_error{ "system not found." };
        }

        _logger->log_info("removing system done.");
        return { create_from_void };
    }

    auto system_manager::remove_system(system* system) -> result<void, no_entry_error>
    {
        _logger->log_info("removing system '{}'", system->get_name());

        bool removed =
            _systems.remove_one_if([&](const auto& entry) { return entry.second == system; });

        if (not removed)
        {
            _logger->log_error("removing system failed, not found.");
            return no_entry_error{ "system not found." };
        }

        _logger->log_info("removing system done.");
        return { create_from_void };
    }

    auto system_manager::get_system(type_id id) -> system*
    {
        auto it = _systems | ranges::find_if([&](const auto& entry) { return entry.first == id; });

        if (it == _systems.get_iterator_end())
        {
            return nullptr;
        }

        return it->second;
    }

    auto system_manager::has_system(type_id id) -> bool
    {
        return _has_system(id);
    }

    auto system_manager::update_systems(time_step time) -> void
    {
        for (const auto& entry : _systems)
        {
            system* system = entry.second;
            system->on_update(time);
        }
    }

    auto system_manager::_has_system(type_id id) -> bool
    {
        return _systems | ranges::contains_if([&](const auto& entry) { return entry.first == id; });
    }
}
