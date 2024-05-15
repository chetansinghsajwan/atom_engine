export module atom.engine:rendering.vertex_array;

import atom.core;
import :rendering.vertex_buffer;
import :rendering.index_buffer;

namespace atom::engine
{
    // @todo: remove this export.
    export class vertex_array
    {
    public:
        vertex_array() {}

        virtual ~vertex_array() {}

    public:
        static auto create() -> vertex_array*;

    public:
        virtual auto bind() -> void = 0;
        virtual auto unbind() -> void = 0;

        virtual auto add_vertex_buffer(vertex_buffer* buffer) -> void = 0;
        virtual auto get_vertex_buffers() const -> array_view<vertex_buffer*> = 0;

        virtual auto set_index_buffer(index_buffer* buffer) -> void = 0;
        virtual auto get_index_buffer() const -> index_buffer* = 0;
    };
}
