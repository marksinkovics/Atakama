#ifndef ATAKAMA_RENDERER_HPP
#define ATAKAMA_RENDERER_HPP

#include "Atakama/Engine/Camera.hpp"
#include "Atakama/Engine/Shader.hpp"
#include "Atakama/Engine/SubMesh.hpp"

#include "Atakama/Engine/RenderSystem.hpp"

namespace Atakama
{

class Renderer
{
public:
    Renderer(Ref<RenderSystem> renderSystem, Ref<Camera>& camera, Ref<Shader> shader);
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
