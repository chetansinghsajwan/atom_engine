export module atom.engine:rendering.texture;

import atom.core;

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
        texture(texture_format format)
            : _format{ format }
        {}

        virtual ~texture() {}

    public:
        auto get_format() const -> texture_format
        {
            return _format;
        }

        virtual auto get_renderer_id() const -> u32 = 0;
        virtual auto get_height() const -> u32 = 0;
        virtual auto get_width() const -> u32 = 0;
        virtual auto bind(u32 slot = 0) -> void = 0;

    private:
        texture_format _format;
    };
}
