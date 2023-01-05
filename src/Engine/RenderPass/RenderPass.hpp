#ifndef RENDER_PASS_HPP
#define RENDER_PASS_HPP

namespace OGLSample
{

class FrameBuffer;
class RenderSystem;
class Scene;
class Shader;
class Texture;

class RenderPass
{
public:
    RenderPass(Ref<RenderSystem> renderSystem);
    virtual ~RenderPass() = default;

protected:
    virtual void Draw();
public:
    virtual void Render();

    virtual Ref<FrameBuffer> GetFrameBuffer();
    virtual Ref<Texture> GetOutputColorTexture();
    virtual Ref<Texture> GetOutputDepthTexture();

    virtual void Resize(glm::uvec2 size);
    virtual glm::uvec2 GetSize();

    virtual void AddDependency(Ref<RenderPass> renderPass);
    virtual void RemoveDependency(Ref<RenderPass> renderPass);

    virtual std::string GetName() = 0;

protected:
    Ref<RenderSystem> m_RenderSystem;
    Ref<FrameBuffer> m_FrameBuffer;

    std::vector<Ref<RenderPass>> m_Dependencies;

    glm::uvec2 m_Size;
};

class SceneRenderPass: public RenderPass
{
public:
    SceneRenderPass(Ref<RenderSystem> renderSystem, Ref<Scene>& scene);
    virtual ~SceneRenderPass() = default;
protected:
    Ref<Scene> m_Scene;
};

}

#endif
