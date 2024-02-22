export module atom.engine:main;
import :application;
import :window_manager;
import atom.core;

using namespace atom;

namespace atom::engine
{
    extern "C++" application* create_application();
}

auto main(int argc, char** args) -> int
{
    window_manager::init();

    engine::application* app = engine::create_application();
    app->run();
    delete app;

    window_manager::shutdown();
}
