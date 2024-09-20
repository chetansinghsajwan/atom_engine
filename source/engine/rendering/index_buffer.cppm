export module atom_engine:rendering.index_buffer;

import atom_core;

namespace atom::engine
{
    class index_buffer
    {
    public:
        static auto create(u32* indices, u32 count) -> index_buffer*;

    public:
        virtual ~index_buffer() {}

    public:
        virtual auto bind() const -> void = 0;
        virtual auto unbind() const -> void = 0;
        virtual auto get_count() const -> u32 = 0;
    };
}
