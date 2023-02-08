#ifndef ATAKAMA_EDITOR_CONTEXT_HPP
#define ATAKAMA_EDITOR_CONTEXT_HPP

namespace Atakama::Editor
{

class RuntimeEditorContext
{
public:
    bool DemohWindowOpen { false };
    bool DepthWindowOpen { false };
    bool StatshWindowOpen { true };

};

extern RuntimeEditorContext g_RuntimeEditorContext;

}

#endif
