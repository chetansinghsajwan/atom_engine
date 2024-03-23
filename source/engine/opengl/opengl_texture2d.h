#pragma once
#include "atom/engine/rendering/texture2d.h"

namespace atom::engine
{
    class opengl_texture2d: public texture2d
    {
    public:
        opengl_texture2d(string_view file_path);
        virtual ~opengl_texture2d();

    public:
        virtual auto get_height() const -> u32 override final
        {
            return _height;
        }

        virtual auto get_width() const -> u32 override final
        {
            return _width;
        }

        virtual auto bind(u32 slot = 0) -> void override;

    private:
        string _file_path;
        u32 _renderer_id;
        u32 _height;
        u32 _width;
    };
}
