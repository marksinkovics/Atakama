#ifndef ATAKAMA_EDITOR_CONTEXT_HPP
#define ATAKAMA_EDITOR_CONTEXT_HPP

namespace Atakama::Editor
{

class RuntimeEditorContext
{
public:
    void Init();
    void Shutdown();

    std::map<WindowId, WindowConfig> WindowConfigs;
    EditorUIConfig UIConfig;
};

WindowConfig& GetWindowConfig(WindowId windowId);
std::string GetImGuiWindowId(WindowId windowId);
EditorUIConfig& GetUIConfig();

extern RuntimeEditorContext g_RuntimeEditorContext;

}

#endif
