#ifndef ATAKAMA_RENDER_SYSTEM_HPP
#define ATAKAMA_RENDER_SYSTEM_HPP

#include "RenderTypes.hpp"

namespace Atakama
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

class Shader;
class Entity;

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

    virtual void Draw(Entity& entity, Ref<Shader>& shader);
    
    static Ref<RenderSystem> Create();


    virtual std::string GetVendor() = 0;
    virtual std::string GetRenderer() = 0;
    virtual std::string GetVersion() = 0;
    virtual std::string GetShadingLanguageVersion() = 0;
};

}

#endif
