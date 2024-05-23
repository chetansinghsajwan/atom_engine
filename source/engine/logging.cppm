export module atom.engine:logging;

import atom.core;
import atom.logging;

namespace atom::engine
{
    export class log_manager
    {
    public:
        static auto initialize() -> void
        {
            logging::logger_manager::initialize();
        }

        static auto finalize() -> void
        {
            logging::logger_manager::finalize();
        }

        static auto get_global_logger() -> logging::logger*
        {
            return logging::logger_manager::get_default_logger();
        }
    };

    template <typename... arg_types>
    constexpr auto ATOM_ENGINE_LOG_TRACE(format_string<arg_types...> fmt, arg_types&&... args) -> void
    {
        log_manager::get_global_logger()->log_trace(fmt, forward<arg_types>(args)...);
    }

    template <typename... arg_types>
    constexpr auto ATOM_ENGINE_LOG_DEBUG(format_string<arg_types...> fmt, arg_types&&... args) -> void
    {
        log_manager::get_global_logger()->log_debug(fmt, forward<arg_types>(args)...);
    }

    template <typename... arg_types>
    constexpr auto ATOM_ENGINE_LOG_INFO(format_string<arg_types...> fmt, arg_types&&... args) -> void
    {
        log_manager::get_global_logger()->log_info(fmt, forward<arg_types>(args)...);
    }

    template <typename... arg_types>
    constexpr auto ATOM_ENGINE_LOG_WARN(format_string<arg_types...> fmt, arg_types&&... args) -> void
    {
        log_manager::get_global_logger()->log_warn(fmt, forward<arg_types>(args)...);
    }

    template <typename... arg_types>
    constexpr auto ATOM_ENGINE_LOG_ERROR(format_string<arg_types...> fmt, arg_types&&... args) -> void
    {
        log_manager::get_global_logger()->log_error(fmt, forward<arg_types>(args)...);
    }

    template <typename... arg_types>
    constexpr auto ATOM_ENGINE_LOG_FATAL(format_string<arg_types...> fmt, arg_types&&... args) -> void
    {
        log_manager::get_global_logger()->log_fatal(fmt, forward<arg_types>(args)...);
    }

    template <typename... arg_types>
    constexpr auto ATOM_ENGINE_LOG_PANIC(format_string<arg_types...> fmt, arg_types&&... args) -> void
    {
        ATOM_ENGINE_LOG_FATAL(fmt, forward<arg_types>(args)...);
        contract_panic();
    }
}
