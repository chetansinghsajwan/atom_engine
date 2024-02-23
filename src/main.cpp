export module atom.engine:main;
import :application;
import :window_manager;
import :input_manager;
import atom.core;

using namespace atom;
using namespace atom::engine;

namespace atom::engine
{
    extern "C++" application* create_application();
}

auto main(int argc, char** args) -> int
{
    window_manager::initialize();
    input_manager::initialize();

    engine::application* app = create_application();
    app->run();
    delete app;

    input_manager::finalize();
    window_manager::finalize();

    return 0;
}
