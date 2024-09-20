#include "atom/engine/window/window_manager.h"
#include "atom/engine/inputs/input_manager.h"
#include "atom/engine/rendering/shader_factory.h"
#include "atom/engine/logging.h"
#include "atom/engine/application.h"

using namespace atom::engine;

namespace atom::engine
{
    application* create_application();
}

auto main(int argc, char** args) -> int
{
    log_manager::initialize();
    window_manager::initialize();
    input_manager::initialize();
    shader_factory::initialize();

    application* app = create_application();
    app->run();
    delete app;

    shader_factory::finalize();
    input_manager::finalize();
    window_manager::finalize();
    log_manager::finalize();

    return 0;
}
