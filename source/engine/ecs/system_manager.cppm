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
        template <typename system_type>
        static constexpr bool is_system = typeinfo<system_type>::template is_derived_from<system>;

    public:
        auto initialize() -> void;

        auto finalize() -> void;

        template <typename system_type>
        auto add_system(system_type* system) -> result<void, entry_exists_error>
            requires is_system<system_type>
        {
            return add_system(typeinfo<system_type>::get_id(), system);
        }

        auto add_system(type_id id, system* system) -> result<void, entry_exists_error>;

        template <typename system_type>
        auto remove_system() -> result<void, no_entry_error>
            requires is_system<system_type>
        {
            return remove_system(typeinfo<system_type>::get_id());
        }

        auto remove_system(type_id id) -> result<void, no_entry_error>;

        auto remove_system(system* system) -> result<void, no_entry_error>;

        template <typename system_type, typename... arg_types>
        auto emplace_system(arg_types&&... args) -> result<system_type*, entry_exists_error>
            requires is_system<system_type>
        {
            type_id id = typeinfo<system_type>::get_id();
            _logger->log_info("emplacing system with id '{}'...", id);

            if (_has_system(id))
            {
                _logger->log_error("emplacing system failed, system already exists.");
                return entry_exists_error{ "system already exists." };
            }

            system_type* system = new system_type{ forward<arg_types>(args)... };
            _systems.emplace_back(id, system);

            _logger->log_info("emplacing system done.");
        }

        template <typename system_type, typename... arg_types>
        auto get_or_emplace_system(arg_types&&... args) -> system_type*
            requires is_system<system_type>
        {
            system_type* system = get_system<system_type>();
            if (system == nullptr)
            {
                system =
                    emplace_system<system_type>(forward<arg_types>(args)...).get_value_checked();
            }

            return system;
        }

        template <typename system_type>
        auto get_system() -> system_type*
            requires is_system<system_type>
        {
            type_id id = typeinfo<system_type>::get_id();
            system* system = get_system(id);
            return reinterpret_cast<system_type*>(system);
        }

        auto get_system(type_id id) -> system*;

        template <typename system_type>
        auto has_system() -> bool
        {
            return has_system(typeinfo<system_type>::get_id());
        }

        auto has_system(type_id id) -> bool;

        auto update_systems(time_step time) -> void;

    private:
        auto _add_system(type_id id, system* system) -> void;

        auto _has_system(type_id id) -> bool;

        auto _remove_system(type_id id, system* system) -> bool;

    private:
        logging::logger* _logger;
        dynamic_array<pair<type_id, system*>> _systems;
    };
}
