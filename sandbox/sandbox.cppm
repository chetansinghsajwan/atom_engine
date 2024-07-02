export module atom.engine.sandbox;

import atom_core;
import atom.engine;
import :sandbox2d_layer;

class sandbox_application: public engine::application
{
public:
    sandbox_application()
        : engine::application{ "sandbox" }
    {
        _layer = new sandbox2d_layer();
        push_layer(_layer);
    }

    ~sandbox_application()
    {
        delete _layer;
    }

private:
    sandbox2d_layer* _layer;
};

namespace atom::engine
{
    extern "C++" application* create_application()
    {
        return new sandbox_application();
    }
}
