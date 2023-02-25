#ifndef ATAKAMA_OPENGL3_RENDER_SYSTEM_HPP
#define ATAKAMA_OPENGL3_RENDER_SYSTEM_HPP

#include "Atakama/Engine/RenderSystem.hpp"

namespace Atakama
{

class VertexArray;

class OpenGL3RenderSystem: public RenderSystem
{
public:
    virtual void Init() override;
    virtual void Clear() const  override;
    virtual void SetClearColor(const glm::vec4& clearColor)  override;
    virtual void SetDepthTest(bool value) override;
    virtual void SetDepthCompare(DepthCompare depthCompare) override;
    virtual void Draw(DrawingMode mode, Ref<VertexArray>& vertexArray) override;
    virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

    virtual std::string GetVendor() override;
    virtual std::string GetRenderer() override;
    virtual std::string GetVersion() override;
};

}

#endif
