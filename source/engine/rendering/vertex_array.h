#pragma once
#include "engine/rendering/buffer_layout.h"
#include "engine/rendering/vertex_buffer.h"
#include "engine/rendering/index_buffer.h"

namespace atom::engine
{
    class vertex_array
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
