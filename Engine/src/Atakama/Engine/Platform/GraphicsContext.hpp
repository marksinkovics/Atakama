#ifndef ATAKAMA_GRAPHICS_CONTEXT_HPP
#define ATAKAMA_GRAPHICS_CONTEXT_HPP

#include "Atakama/Engine/RenderTypes.hpp"

namespace Atakama
{

class GraphicsContext
{
public:
    virtual ~GraphicsContext() = default;
    
    virtual void Init() = 0;
    virtual void Register(void *window) = 0;
    virtual void SwapBuffers() = 0;
    virtual void SetVSync(bool enable) = 0;
    virtual bool GetVSync() const = 0;
    
    static Ref<GraphicsContext> Create();
};

}

#endif
