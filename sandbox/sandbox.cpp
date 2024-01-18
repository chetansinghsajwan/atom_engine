import atom.core;
import atom.logging;
import atom.engine;

using namespace atom;
using namespace atom::logging;
using namespace atom::engine;

class sandbox_application: public application
{};

namespace atom::engine
{
    extern application* create_application()
    {
        shared_ptr<console_log_target> target = make_shared<console_log_target>();

        simple_logger_st logger(make_range("test"), make_range({ target }));
        logger.set_log_level(log_level::debug);

        logger.log_warn("just a warning");

        return new sandbox_application();
    }
}
