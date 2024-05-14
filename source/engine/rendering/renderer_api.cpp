import atom.core;
import atom.logging;

#include "renderer_api.h"

namespace atom::engine
{
    renderer_api::api renderer_api::_api = renderer_api::api::opengl;
}
