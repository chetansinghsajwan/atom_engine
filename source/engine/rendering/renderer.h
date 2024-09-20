#pragma once
#include "renderer_api.h"
#include "engine/rendering/render_command.h"
#include "engine/rendering/orthographic_camera.h"
#include "atom/engine/rendering/shader.h"

namespace atom::engine
{
    class renderer
    {
    public:
        static auto initialize() -> void;
        static auto finalize() -> void;
    
        static auto get_api() -> renderer_api::api
        {
            return renderer_api::get_api();
        }

        static auto begin_scene(orthographic_camera* camera) -> void;
        static auto end_scene() -> void;
        static auto submit(class shader* shader, vertex_array* arr, const glm::mat4& transform) -> void;

        static auto on_window_resize(u32 width, u32 height) -> void;

    private:
        struct scene_data
        {
            glm::mat4 view_projection_matrix;
        };

        static scene_data* _data;
    };
}
