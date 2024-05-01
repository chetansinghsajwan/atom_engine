#include "atom.engine.h"
#include "atom/engine/rendering/texture2d.h"
#include "engine/rendering/vertex_array.h"
#include "engine/rendering/orthographic_camera_controller.h"

namespace sandbox
{
    class sandbox_layer_2d: public atom::engine::layer
    {
    public:
        sandbox_layer_2d();
        ~sandbox_layer_2d();

    public:
        virtual auto on_attach() -> void override;
        virtual auto on_update(atom::engine::time_stemp delta_time) -> void override;
        virtual auto on_imgui_render() -> void override;

    private:
        auto _setup_logging() -> void;
        auto _setup_window() -> void;
        auto _setup_keyboard() -> void;
        auto _setup_mouse() -> void;
        auto _setup_rendering() -> void;

    private:
        atom::logging::logger* _logger;
        std::unique_ptr<atom::engine::shader> _flat_color_shader;
        std::unique_ptr<atom::engine::vertex_array> _square_vertex_array;
        atom::engine::orthographic_camera_controller _camera_controller;
        atom::engine::vec4 _square_color;
        atom::engine::window* _window;
        atom::engine::keyboard* _keyboard;
        atom::engine::mouse* _mouse;
    };
}
