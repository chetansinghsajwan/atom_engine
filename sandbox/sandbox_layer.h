#include "atom.engine.h"
#include "atom/engine/rendering/texture2d.h"
#include "engine/rendering/vertex_array.h"
#include "engine/rendering/orthographic_camera_controller.h"

namespace sandbox
{
    class sandbox_layer: public atom::engine::layer
    {
    public:
        sandbox_layer();
        ~sandbox_layer();

    public:
        virtual auto on_attach() -> void override;
        virtual auto on_update(atom::engine::time_stemp delta_time) -> void override;

    private:
        auto _setup_logging() -> void;
        auto _setup_window() -> void;
        auto _setup_keyboard() -> void;
        auto _setup_mouse() -> void;
        auto _setup_rendering() -> void;

    private:
        atom::logging::logger* _logger;
        std::shared_ptr<atom::engine::texture2d> _checkerboard_texture;
        std::shared_ptr<atom::engine::texture2d> _cherno_texture;
        std::unique_ptr<atom::engine::shader> _texture_shader;
        std::unique_ptr<atom::engine::vertex_array> _vertex_array;
        atom::engine::orthographic_camera_controller _camera_controller;
        atom::engine::window* _window;
        atom::engine::keyboard* _keyboard;
        atom::engine::mouse* _mouse;
    };
}
