export module atom.engine:logging;

import atom.core;
import atom.logging;

namespace atom::engine
{
    logging::logger* global_logger = nullptr;

    export class log_manager
    {
    public:
        static auto initialize() -> void
        {
            logging::logger_manager::initialize();
            global_logger = logging::logger_manager::get_default_logger();
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
