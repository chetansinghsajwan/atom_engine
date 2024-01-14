#include "Atom/Engine.h"
#include "Atom/Logging/LogTargets/ConsoleLogTarget.h"
#include "Atom/Logging/SimpleLogger.h"
#include "Atom/Range.h"
#include <iostream>

using namespace Atom;
using namespace Atom::Engine;
using namespace Atom::Logging;

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
