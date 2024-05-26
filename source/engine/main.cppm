export module atom.engine:main;

#include "config.h"

import :logging;
import :windows;
import :inputs;
import :rendering;
import :application;

using namespace atom::engine;

namespace atom::engine
{
    extern "C++" application* create_application();
}

auto main(int argc, char** args) -> int
{
    renderer_2d::assets_path = ATOM_ENGINE_ASSETS_DIR;

    log_manager::initialize();
    window_manager::initialize();
    input_manager::initialize();
    shader_factory::initialize();
    shader_registry::initialize();

    application* app = create_application();
    app->run();
    delete app;

    shader_registry::finalize();
    shader_factory::finalize();
    input_manager::finalize();
    window_manager::finalize();
    log_manager::finalize();

    return 0;
}
