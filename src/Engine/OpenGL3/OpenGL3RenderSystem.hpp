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
    virtual void SetDepthTest(bool value) override;
    virtual void Draw(DrawingMode mode, Ref<VertexArray>& vertexArray) const override;
    virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
};

}

#endif
