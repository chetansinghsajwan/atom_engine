#include "atom.engine.h"
#include "atom/engine/rendering/sprite.h"
#include "atom/engine/rendering/texture2d.h"
#include "engine/rendering/vertex_array.h"
#include "engine/rendering/orthographic_camera_controller.h"
#include "engine/rendering/renderer_2d.h"

namespace atom::editor
{
    class editor_layer: public engine::layer
    {
    public:
        editor_layer();
        ~editor_layer();

    public:
        virtual auto on_attach() -> void override;
        virtual auto on_update(engine::time_stemp delta_time) -> void override;
        virtual auto on_imgui_render() -> void override;

    private:
        auto _setup_logging() -> void;
        auto _setup_window() -> void;
        auto _setup_keyboard() -> void;
        auto _setup_mouse() -> void;

    private:
        logging::logger* _logger;
        engine::orthographic_camera_controller _camera_controller;
        engine::texture2d* _rpg_texture;
        engine::sprite* _stairs_sprite;
        engine::sprite* _barrel_sprite;
        engine::sprite* _tree_sprite;
        engine::window* _window;
        engine::keyboard* _keyboard;
        engine::mouse* _mouse;

        engine::frame_buffer* _frame_buffer;
    };
}
