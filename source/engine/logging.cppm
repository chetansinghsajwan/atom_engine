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

    constexpr auto ATOM_ENGINE_LOG_TRACE(auto&&... args) -> void
    {
        // log_manager::get_global_logger()->log_trace(
        //     runtime_format_string(forward<decltype(args)>(args)...));
    }

    constexpr auto ATOM_ENGINE_LOG_DEBUG(auto&&... args) -> void
    {
        // log_manager::get_global_logger()->log_debug(
        //     runtime_format_string(forward<decltype(args)>(args)...));
    }

    constexpr auto ATOM_ENGINE_LOG_INFO(auto&&... args) -> void
    {
        // log_manager::get_global_logger()->log_info(
        //     runtime_format_string(forward<decltype(args)>(args)...));
    }

    constexpr auto ATOM_ENGINE_LOG_WARN(auto&&... args) -> void
    {
        // log_manager::get_global_logger()->log_warn(
        //     runtime_format_string(forward<decltype(args)>(args)...));
    }

    constexpr auto ATOM_ENGINE_LOG_ERROR(auto&&... args) -> void
    {
        // log_manager::get_global_logger()->log_error(
        //     runtime_format_string(forward<decltype(args)>(args)...));
    }

    constexpr auto ATOM_ENGINE_LOG_FATAL(auto&&... args) -> void
    {
        // log_manager::get_global_logger()->log_fatal(
        //     runtime_format_string(forward<decltype(args)>(args)...));
    }

    constexpr auto ATOM_ENGINE_LOG_PANIC(auto&&... args) -> void
    {
        ATOM_ENGINE_LOG_FATAL(forward<decltype(args)>(args)...);
        ATOM_PANIC();
    }
}
