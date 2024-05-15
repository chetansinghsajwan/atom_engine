export module atom.engine.sandbox;

import atom.core;
import atom.engine;
import :layer2d;

namespace sandbox
{
    class sandbox_application: public engine::application
    {
    public:
        sandbox_application()
            : engine::application("sandbox")
        {
            _layer = new sandbox_layer_2d();
            push_layer(_layer);
        }

        ~sandbox_application()
        {
            delete _layer;
        }

    private:
        sandbox_layer_2d* _layer;
    };
}

namespace atom::engine
{
    extern "C++" application* create_application()
    {
        return new sandbox::sandbox_application();
    }
}
