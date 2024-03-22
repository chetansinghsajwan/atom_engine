#include "renderer.h"

namespace atom::engine
{
    auto renderer::begin_scene(orthographic_camera* camera) -> void {
        _data->view_projection_matrix = camera->get_view_projection_matrix();
    }

    auto renderer::end_scene() -> void {}

    auto renderer::submit(class shader* shader, vertex_array* arr) -> void
    {
        shader->bind();
        shader->upload_uniform_mat4("u_view_projection", _data->view_projection_matrix);
        
        arr->bind();
        render_command::draw_indexed(arr);
    }

    renderer::scene_data* renderer::_data = new renderer::scene_data();
}
