#include "engine/rendering/shader_factory_impl.h"
#include "engine/opengl/opengl_shader.h"

namespace atom::engine
{
    class opengl_shader_factory_impl: public shader_factory_impl
    {
    public:
        virtual auto create(string_view vertex_source, string_view fragment_source) -> opengl_shader* override;
        virtual auto destroy(shader* shader) -> void override;
    };
}
