#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include "RenderTypes.hpp"

namespace OGLSample
{

class VertexArray;

enum class DepthCompare
{
    Never,
    Less,
    Equal,
    LessOrEqual,
    Greater,
    NotEqual,
    GreaterOrEqual,
    Always,
};

class RenderSystem
{
public:
    virtual void Init() = 0;
    virtual void Clear() const = 0;
    virtual void SetClearColor(const glm::vec4& clearColor) = 0;
    virtual void SetDepthTest(bool value) = 0;
    virtual void SetDepthCompare(DepthCompare depthCompare) = 0;
    virtual void Draw(DrawingMode mode, Ref<VertexArray>& vertexArray) = 0;
    virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
    
    static Ref<RenderSystem> Create();
};

}

#endif
