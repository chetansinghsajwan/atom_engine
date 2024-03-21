#pragma once
#include "atom.core.h"
#include "engine/rendering/vertex_array.h"

namespace atom::engine
{
    class opengl_vertex_array: public vertex_array
    {
    public:
        opengl_vertex_array();
        virtual ~opengl_vertex_array();

    public:
        virtual auto bind() -> void override;
        virtual auto unbind() -> void override;

        virtual auto add_vertex_buffer(vertex_buffer* buffer) -> void override;
        virtual auto get_vertex_buffers() const -> array_view<vertex_buffer*> override;

        virtual auto set_index_buffer(index_buffer* buffer) -> void override;
        virtual auto get_index_buffer() const -> index_buffer* override;

    private:
        unsigned int _renderer_id;
        dynamic_array<vertex_buffer*> _vertex_buffers;
        index_buffer* _index_buffer;
    };
}
