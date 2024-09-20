#include "renderer.h"
#include "engine/opengl/opengl_shader.h"
#include "engine/rendering/render_command.h"
#include "atom/engine/logging.h"

namespace atom::engine
{
    auto renderer::initialize() -> void
    {
        ATOM_ENGINE_LOG_INFO("initializing renderer...");
        render_command::initialize();
        ATOM_ENGINE_LOG_INFO("initializing renderer done.");
    }

    auto renderer::finalize() -> void
    {
        ATOM_ENGINE_LOG_INFO("finalizing renderer...");
        render_command::finalize();
        ATOM_ENGINE_LOG_INFO("finalizing renderer done.");
    }

    auto renderer::begin_scene(orthographic_camera* camera) -> void
    {
        _data->view_projection_matrix = camera->get_view_projection_matrix();
    }

    auto renderer::end_scene() -> void {}

    auto renderer::submit(class shader* shader, vertex_array* arr, const glm::mat4& transform)
        -> void
    {
        shader->bind();

        static_cast<opengl_shader*>(shader)->upload_uniform_mat4(
            "u_view_projection", _data->view_projection_matrix);

        static_cast<opengl_shader*>(shader)->upload_uniform_mat4("u_transform", transform);

        arr->bind();
        render_command::draw_indexed(arr);
    }

    renderer::scene_data* renderer::_data = new renderer::scene_data();
}
