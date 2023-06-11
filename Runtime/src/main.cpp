#include "RuntimeApplication.hpp"

#include <Atakama/Core/Args.hpp>

int main(int argc, char **argv)
{
    Atakama::g_RuntimeGlobalContext.Init();
    Atakama::g_RuntimeGlobalContext.m_Editor = false;
    Atakama::SetArguments({argc, argv});

    {
        Atakama::Runtime::RuntimeApplication app;
        app.Run();
    }

    Atakama::g_RuntimeGlobalContext.Shutdown();
    
    return 0;
}
