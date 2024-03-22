#include "atom.engine.h"
#include "sandbox_layer.h"

using namespace atom;
using namespace atom::logging;
using namespace atom::engine;

namespace sandbox
{
    class sandbox_application: public application
    {
    public:
        sandbox_application()
        {
            _layer = new sandbox_layer();
            push_layer(_layer);
        }

    private:
        sandbox_layer* _layer;
    };
}

namespace atom::engine
{
    extern application* create_application()
    {
        return new sandbox::sandbox_application();
    }
}
