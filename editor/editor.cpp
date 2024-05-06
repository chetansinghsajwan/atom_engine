#include "atom.engine.h"
#include "editor_layer.h"

using namespace atom;
using namespace atom::logging;
using namespace atom::engine;

namespace atom::editor
{
    class editor_application: public application
    {
    public:
        editor_application()
            : application("hazel-editor")
        {
            _layer = new editor_layer();
            push_layer(_layer);
        }

    private:
        editor_layer* _layer;
    };
}

namespace atom::engine
{
    extern application* create_application()
    {
        return new editor::editor_application();
    }
}
