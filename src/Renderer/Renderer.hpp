#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Engine/Camera.hpp"
#include "Engine/Shader.hpp"
#include "Engine/SubMesh.hpp"

#include "Engine/RenderSystem.hpp"

namespace OGLSample
{

class Renderer
{
public:
    Renderer() {}

    virtual void Init(Ref<RenderSystem> renderSystem, Ref<Camera> camera, Ref<Shader> shader);
    virtual ~Renderer() = default;

    virtual void Begin();
    virtual void Draw();
    virtual void End();

protected:
    Ref<Shader> m_Shader;
    Ref<Camera> m_Camera;
    Ref<RenderSystem> m_RenderSystem;
};

}

#endif
