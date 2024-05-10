#include "atom.engine.h"
#include "atom/engine/rendering/sprite.h"
#include "atom/engine/rendering/texture2d.h"
#include "engine/rendering/vertex_array.h"
#include "engine/rendering/orthographic_camera_controller.h"
#include "engine/rendering/renderer_2d.h"
#include "atom/engine/ecs.h"
#include "atom/engine/rendering/scene.h"
#include "panels/entity_explorer_panel.h"

namespace atom::editor
{
    class editor_layer: public engine::layer
    {
    public:
        editor_layer();
        ~editor_layer();

    public:
        virtual auto on_attach() -> void override;
        virtual auto on_update(engine::time_step delta_time) -> void override;
        virtual auto on_imgui_render() -> void override;

    private:
        auto _setup_logging() -> void;
        auto _setup_window() -> void;
        auto _setup_keyboard() -> void;
        auto _setup_mouse() -> void;

    private:
        logging::logger* _logger;
        // engine::orthographic_camera_controller _camera_controller;
        engine::entity* _camera_entity;
        engine::texture2d* _rpg_texture;
        engine::sprite* _stairs_sprite;
        engine::entity* _stairs_entity;
        engine::sprite* _barrel_sprite;
        engine::sprite* _tree_sprite;
        engine::window* _window;
        engine::keyboard* _keyboard;
        engine::mouse* _mouse;
        engine::scene* _scene;
        engine::entity_manager* _entity_manager;

        engine::frame_buffer* _frame_buffer;
        engine::vec2 _viewport_size = engine::vec2{ 0, 0 };
        bool _is_viewport_focused = false;
        bool _is_viewport_hovered = false;

        entity_explorer_panel* _entity_explorer_panel;
    };
}
