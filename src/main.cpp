#include "atom/engine/window/window_manager.h"
#include "atom/engine/inputs/input_manager.h"
#include "atom/engine/application.h"

using namespace atom;
using namespace atom::logging;
using namespace atom::engine;

namespace atom::engine
{
    application* create_application();
}

auto main(int argc, char** args) -> int
{
    logger_manager::initialize();
    window_manager::initialize();
    input_manager::initialize();

    engine::application* app = create_application();
    app->run();
    delete app;

    input_manager::finalize();
    window_manager::finalize();
    logger_manager::finalize();

    return 0;
}
