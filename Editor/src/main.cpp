#include "EditorApplication.hpp"

#include <Atakama/Core/Args.hpp>

int main(int argc, char **argv)
{
    Atakama::SetArguments({argc, argv});
    Atakama::g_RuntimeGlobalContext.Init();
    Atakama::Editor::g_RuntimeEditorContext.Init();

    {
        Atakama::Editor::EditorApplication app;
        app.Run();
    }

    Atakama::g_RuntimeGlobalContext.Shutdown();
    
    return 0;
}
