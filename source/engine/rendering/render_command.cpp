import atom.core;
import atom.logging;

#include "render_command.h"
#include "engine/opengl/opengl_renderer_api.h"

namespace atom::engine
{
    renderer_api* render_command::_api = new opengl_renderer_api();
}
