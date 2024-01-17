export module atom.engine:main;

import :application;
import atom.core;

using namespace Atom;

auto main(int argc, char** args) -> int
{
    Engine::Application* app = Engine::CreateApplication();
    app->Run();

    delete app;
}
