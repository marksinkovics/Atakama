#include "SandboxApplication.hpp"

#include <Atakama/Core/Args.hpp>

int main(int argc, char **argv)
{
    Atakama::g_RuntimeGlobalContext.Init();
    Atakama::g_RuntimeGlobalContext.m_Editor = false;
    Atakama::SetArguments({argc, argv});

    {
        Atakama::Sandbox::SandboxApplication app;
        app.Run();
    }

    Atakama::g_RuntimeGlobalContext.Shutdown();
    
    return 0;
}
