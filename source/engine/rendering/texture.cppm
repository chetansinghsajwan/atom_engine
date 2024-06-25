export module atom.engine:rendering.texture;

import atom.core;
import :math;

namespace atom::engine
{
    export enum class texture_format
    {
        rgb8,
        rgba8
    };

    export class texture
    {
    public:
        texture(texture_format format, u32vec2 size);
        virtual ~texture();

    public:
        auto get_format() const -> texture_format;
        auto get_size() const -> u32vec2;

    private:
        texture_format _format;
        u32vec2 _size;
    };
}
