#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include "RenderTypes.hpp"

namespace OGLSample
{

class VertexArray;

class RenderSystem
{
public:
    virtual void Init() = 0;
    virtual void Clear() const = 0;
    virtual void SetClearColor(const glm::vec4& clearColor) = 0;
    virtual void Draw(DrawingMode mode, Ref<VertexArray>& vertexArray) const = 0;
    
    static Ref<RenderSystem> Create();
};

}

#endif
