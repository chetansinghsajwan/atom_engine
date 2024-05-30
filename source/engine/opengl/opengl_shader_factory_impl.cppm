export module atom.engine:opengl.shader_factory_impl;

import atom.core;
import atom.logging;
import :rendering;
import :opengl.shader;

namespace atom::engine
{
    class opengl_shader_factory_impl: public shader_factory_impl
    {
    public:
        opengl_shader_factory_impl();
        virtual ~opengl_shader_factory_impl();

    public:
        virtual auto create(
            string_view vertex_source, string_view fragment_source) -> shader* override
        {
            return _create_from_source(vertex_source, fragment_source);
        }

        virtual auto destroy(shader* shader) -> void override
        {
            _destroy(shader);
        }

    private:
        auto _create_from_source(string_view vertex_source, string_view fragment_source) -> shader*;
        auto _destroy(shader* shader) -> void;
        auto _compile(string_view source, int type) -> bool;

        auto _compile_or_get_vulkan_binaries(
            string_view vertex_source, string_view fragment_source) -> void;
        auto _compile_or_get_opengl_binaries() -> void;
        auto _create_program() -> void;
        auto _reflect(int stage, const std::vector<uint32_t>& shaderData) -> void;

    private:
        logging::logger* _logger = nullptr;
    };
}
