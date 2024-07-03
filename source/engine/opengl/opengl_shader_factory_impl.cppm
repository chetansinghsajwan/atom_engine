export module atom_engine:opengl.shader_factory_impl;

import atom_core;
import atom_logging;
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

    private:
        logging::logger* _logger = nullptr;
    };
}
