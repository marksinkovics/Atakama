#ifndef OPENGL3_RENDER_SYSTEM_HPP
#define OPENGL3_RENDER_SYSTEM_HPP

#include "Engine/RenderSystem.hpp"

namespace OGLSample
{

class VertexArray;

class OpenGL3RenderSystem: public RenderSystem
{
public:
    virtual void Init() override;
    virtual void Clear() const  override;
    virtual void SetClearColor(const glm::vec4& clearColor)  override;
    virtual void Draw(DrawingMode mode, Ref<VertexArray>& vertexArray) const  override;
};

}

#endif
