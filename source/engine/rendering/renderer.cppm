export module atom.engine:rendering.renderer;

import atom.core;
import :math;
import :rendering.render_command;
import :rendering.renderer_api;
import :rendering.renderer_2d;
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
            ATOM_ENGINE_LOG_INFO("initializing renderer...");

            render_command::initialize();
            renderer_2d::initialize();

            ATOM_ENGINE_LOG_INFO("initializing renderer done.");
        }

        static auto finalize() -> void
        {
            ATOM_ENGINE_LOG_INFO("finalizing renderer...");

            renderer_2d::finalize();
            render_command::finalize();

            ATOM_ENGINE_LOG_INFO("finalizing renderer done.");
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

        static auto submit(
            class shader* shader, vertex_array* arr, const mat4& transform) -> void
        {
            shader->bind();
            shader->set_uniform_mat4("u_view_projection", _data->view_projection_matrix);
            shader->set_uniform_mat4("u_transform", transform);

            arr->bind();
            render_command::draw_indexed(arr);
        }

        static auto on_window_resize(u32 width, u32 height) -> void
        {
            render_command::set_viewport(0, 0, width, height);
        }

    private:
        struct scene_data
        {
            mat4 view_projection_matrix;
        };

        static inline scene_data* _data = new scene_data();
    };
}
