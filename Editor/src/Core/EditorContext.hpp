#ifndef ATAKAMA_EDITOR_CONTEXT_HPP
#define ATAKAMA_EDITOR_CONTEXT_HPP

namespace Atakama::Editor
{

class RuntimeEditorContext
{
public:
    bool DemoWindowOpen { false };
    bool DepthWindowOpen { false };
    bool StatshWindowOpen { true };

    bool SceneViewOpen { true };
    bool ObjectPropertiesViewOpen { true };

};

extern RuntimeEditorContext g_RuntimeEditorContext;

}

#endif
