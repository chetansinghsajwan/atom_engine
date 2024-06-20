export module atom.engine:rendering.renderer;

import atom.core;
import atom.logging;
import :math;
import :rendering.render_command;
import :rendering.renderer_api;
import :rendering.renderer2d;
import :rendering.vertex_array;
import :rendering.shader;
import :rendering.orthographic_camera;

namespace atom::engine
{
    class renderer
    {
    public:
        static auto initialize() -> void
        {
            _logger = logging::logger_manager::create_logger({ .name = "renderer" }).get_value();
            _logger->log_info("initializing renderer...");

            render_command::initialize();
            renderer2d::initialize();

            _logger->log_info("initializing renderer done.");
        }

        static auto finalize() -> void
        {
            _logger->log_info("finalizing renderer...");

            renderer2d::finalize();
            render_command::finalize();

            _logger->log_info("finalizing renderer done.");
        }

        static auto get_api() -> renderer_api::api
        {
            return renderer_api::get_api();
        }

        static auto begin_scene(orthographic_camera* camera) -> void
        {
            _data->view_projection_matrix = camera->get_view_projection_matrix();
        }

        static auto end_scene() -> void {}

        static auto on_window_resize(u32 width, u32 height) -> void
        {
            render_command::set_viewport(0, 0, width, height);
        }

    private:
        struct scene_data
        {
            f32mat4 view_projection_matrix;
        };

        static inline scene_data* _data = new scene_data();
        static inline logging::logger* _logger = nullptr;
    };
}
