#include "atom.engine.h"
#include "atom/engine/rendering/sprite.h"
#include "atom/engine/rendering/texture2d.h"
#include "engine/rendering/vertex_array.h"
#include "engine/rendering/orthographic_camera_controller.h"
#include "engine/rendering/renderer_2d.h"

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

    private:
        atom::logging::logger* _logger;
        atom::engine::orthographic_camera_controller _camera_controller;
        atom::engine::texture2d* _rpg_texture;
        atom::engine::sprite* _stairs_sprite;
        atom::engine::sprite* _barrel_sprite;
        atom::engine::sprite* _tree_sprite;
        atom::engine::window* _window;
        atom::engine::keyboard* _keyboard;
        atom::engine::mouse* _mouse;

        atom::engine::frame_buffer* _frame_buffer;
    };
}
