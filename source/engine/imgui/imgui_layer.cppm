export module atom.engine:imgui.layer;

import atom_core;
import :glfw;
import :application;

namespace atom::engine
{
    class imgui_layer: public layer
    {
    public:
        imgui_layer();

        ~imgui_layer();

    public:
        virtual auto on_attach() -> void override;

        virtual auto on_deattach() -> void override;

        virtual auto on_imgui_render() -> void override;

        auto begin_render() -> void;

        auto end_render() -> void;

        auto setup_imgui_theme() -> void;

    private:
        f64 _time;
    };
}
