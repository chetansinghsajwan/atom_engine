#include "atom.engine.h"

using namespace atom;
using namespace atom::logging;
using namespace atom::engine;

class sandbox_application: public application
{};

namespace atom::engine
{
    extern application* create_application()
    {
        return new sandbox_application();
    }
}
