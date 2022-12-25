#include "Application.hpp"
#include "Args.hpp"
#include "GlobalContext.hpp"

int main(int argc, char **argv)
{
    OGLSample::g_RuntimeGlobalContext.Init();

    OGLSample::SetArguments({argc, argv});

    OGLSample::Application app;
    app.run();

    OGLSample::g_RuntimeGlobalContext.Shutdown();
    
    return 0;
}
