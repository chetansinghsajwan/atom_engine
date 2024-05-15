module;
#include "glad/glad.h"
#include "GLFW/glfw3.h"

export module atom.engine:opengl.renderer_api;

import atom.core;
import :logging;
import :math;
import :rendering;

namespace atom::engine
{
    class opengl_renderer_api: public renderer_api
    {
    public:
        virtual auto initialize() -> void override
        {
            ATOM_ENGINE_LOG_INFO("initializing opengl_renderer...");

            glEnable(GL_BLEND);
            glEnable(GL_DEPTH_TEST);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            ATOM_ENGINE_LOG_INFO("initializing opengl_renderer done.");
        }

        virtual auto finalize() -> void override
        {
            ATOM_ENGINE_LOG_INFO("finalizing opengl_renderer...");
            ATOM_ENGINE_LOG_INFO("finalizing opengl_renderer done.");
        }

        virtual auto set_clear_color(vec4 color) -> void override
        {
            glClearColor(color.r, color.g, color.b, color.a);
        }

        virtual auto clear_color() -> void override
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        virtual auto draw_indexed(vertex_array* arr, u32 index_count = 0) -> void override
        {
            // if (index_count == 0)
            // {
            //     index_count = arr->get_index_buffer()->get_count();
            // }

            uint32_t count = index_count ? arr->get_index_buffer()->get_count() : index_count;
            glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        virtual auto set_viewport(u32 x, u32 y, u32 width, u32 height) -> void override
        {
            glViewport(x, y, width, height);
        }
    };
}
