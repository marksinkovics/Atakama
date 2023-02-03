#include "Application.hpp"
#include "Args.hpp"
#include "GlobalContext.hpp"

int main(int argc, char **argv)
{
    Atakama::g_RuntimeGlobalContext.Init();

    Atakama::SetArguments({argc, argv});

    {
        Atakama::Ref<Atakama::Application> app = Atakama::CreateRef<Atakama::Application>();
        Atakama::g_RuntimeGlobalContext.m_Application = app;

        app->run();

        Atakama::g_RuntimeGlobalContext.m_Application.reset();
    }

    Atakama::g_RuntimeGlobalContext.Shutdown();
    
    return 0;
}
