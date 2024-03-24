#include "atom/engine/rendering/shader_factory.h"
#include "atom/engine/logging.h"
#include "engine/rendering/shader_factory_impl.h"
#include "engine/opengl/opengl_shader_factory_impl.h"

namespace atom::engine
{
    static shader_factory_impl* _impl;
    static logging::logger* _logger;

    auto shader_factory::initialize() -> void
    {
        _logger = logging::logger_manager::create_logger({ .name = "shader_factory" }).get_at<0>();
        _impl = new opengl_shader_factory_impl();
    }

    auto shader_factory::finalize() -> void
    {
        delete _impl;
        delete _logger;
    }

    auto shader_factory::create_from_source(string_view vertex_source, string_view fragment_source)
        -> shader*
    {
        return _impl->create(vertex_source, fragment_source);
    }

    auto shader_factory::destroy(class shader* shader) -> void
    {
        return _impl->destroy(shader);
    }
}
