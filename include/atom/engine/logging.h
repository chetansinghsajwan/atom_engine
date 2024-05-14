#pragma once
// #include "atom/logging/logger_manager.h"

namespace atom::engine
{
    class log_manager
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
}

#define ATOM_ENGINE_LOG_TRACE(...)                                                                 \
    atom::engine::log_manager::get_global_logger()->log_trace(__VA_ARGS__)

#define ATOM_ENGINE_LOG_DEBUG(...)                                                                 \
    atom::engine::log_manager::get_global_logger()->log_debug(__VA_ARGS__)

#define ATOM_ENGINE_LOG_INFO(...)                                                                  \
    atom::engine::log_manager::get_global_logger()->log_info(__VA_ARGS__)

#define ATOM_ENGINE_LOG_WARN(...)                                                                  \
    atom::engine::log_manager::get_global_logger()->log_warn(__VA_ARGS__)

#define ATOM_ENGINE_LOG_ERROR(...)                                                                 \
    atom::engine::log_manager::get_global_logger()->log_error(__VA_ARGS__)

#define ATOM_ENGINE_LOG_FATAL(...)                                                                 \
    atom::engine::log_manager::get_global_logger()->log_fatal(__VA_ARGS__)

#define ATOM_ENGINE_LOG_PANIC(...)                                                                 \
    ATOM_ENGINE_LOG_FATAL(__VA_ARGS__);                                                            \
    ATOM_PANIC()
