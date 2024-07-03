module;
#include "glad/glad.h"
#include "GLFW/glfw3.h"

module atom_engine:opengl.renderer_api.impl;

import atom_core;
import :opengl.renderer_api;
import :logging;
import :math;
import :rendering;

namespace atom::engine
{
    opengl_renderer_api::opengl_renderer_api()
        {}

    opengl_renderer_api::~opengl_renderer_api()
        {}

    auto opengl_renderer_api::initialize() -> void
    {
        global_logger->log_info("initializing opengl_renderer...");

        glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        global_logger->log_info("initializing opengl_renderer done.");
    }

    auto opengl_renderer_api::finalize() -> void
    {
        global_logger->log_info("finalizing opengl_renderer...");
        global_logger->log_info("finalizing opengl_renderer done.");
    }

    auto opengl_renderer_api::set_clear_color(const class color& color) -> void
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    auto opengl_renderer_api::clear_color() -> void
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    auto opengl_renderer_api::draw_indexed(vertex_array* arr, u32 index_count) -> void
    {
        if (index_count == 0)
        {
            index_count = arr->get_index_buffer()->get_count();
        }

        arr->bind();
        glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    auto opengl_renderer_api::set_viewport(u32 x, u32 y, u32 width, u32 height) -> void
    {
        glViewport(x, y, width, height);
    }
}
