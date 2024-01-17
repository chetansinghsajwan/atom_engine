import atom.core;
import atom.logging;
import atom.engine;

using namespace Atom;
using namespace Atom::Logging;
using namespace Atom::Engine;

class SandboxApplication: public Application
{};

namespace Atom::Engine
{
    extern Application* CreateApplication()
    {
        SharedPtr<ConsoleLogTarget> target = MakeShared<ConsoleLogTarget>();

        SimpleLoggerST logger(MakeRange("Test"), MakeRange({ target }));
        logger.SetLogLevel(ELogLevel::Debug);

        logger.LogWarn("Just a warning");

        return new SandboxApplication();
    }
}
