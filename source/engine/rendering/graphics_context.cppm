export module atom_engine:rendering.graphics_context;

namespace atom::engine
{
    class graphics_context
    {
    public:
        virtual auto initialize() -> void = 0;
        virtual auto finalize() -> void = 0;
        virtual auto swap_buffers() -> void = 0;
    };
}
