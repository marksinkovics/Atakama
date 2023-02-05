#include "EditorApplication.hpp"

#include <Atakama/Core/Args.hpp>

int main(int argc, char **argv)
{
    Atakama::g_RuntimeGlobalContext.Init();
    Atakama::SetArguments({argc, argv});

    {
        Atakama::Editor::EditorApplication app;
        app.Run();
    }

    Atakama::g_RuntimeGlobalContext.Shutdown();
    
    return 0;
}
