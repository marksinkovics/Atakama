#ifndef GRAPHICS_CONTEXT_HPP
#define GRAPHICS_CONTEXT_HPP

#include "Engine/RenderTypes.hpp"

namespace OGLSample
{

class GraphicsContext
{
public:
    virtual ~GraphicsContext() = default;
    
    virtual void Init() = 0;
    virtual void Register(void *window) = 0;
    virtual void SwapBuffers() = 0;
    
    static Ref<GraphicsContext> Create();
};

}

#endif
