export module atom.engine:rendering.frame_buffer;

import atom_core;
import :math;

namespace atom::engine
{
    // @todo: remove this export.
    export struct frame_buffer_specs
    {
        u32 width;
        u32 height;
        u32 samples = 1;
        bool swap_chain_typearget = false;
    };

    // @todo: remove this export.
    export class frame_buffer
    {
    public:
        virtual ~frame_buffer() {}

    public:
        static auto create(const frame_buffer_specs& specs) -> frame_buffer*;

    public:
        virtual auto bind() -> void = 0;
        virtual auto unbind() -> void = 0;
        virtual auto resize(f32vec2 size) -> void = 0;
        virtual auto get_specs() const -> const frame_buffer_specs& = 0;
        virtual auto get_color_attachment_renderer_id() const -> u32 = 0;
    };
}
