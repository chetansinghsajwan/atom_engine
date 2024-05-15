module atom.engine:rendering.render_command.impl;
import :rendering.render_command;

import :opengl.renderer_api;

namespace atom::engine
{
    renderer_api* render_command::_api = new opengl_renderer_api();
}
