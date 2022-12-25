#ifndef LIGHTING_RENDERER_HPP
#define LIGHTING_RENDERER_HPP

#include "Renderer/Renderer.hpp"
#include "Engine/Mesh.hpp"
#include "Engine/Lights/PointLight.hpp"

namespace OGLSample
{

class LightingRenderer: public Renderer
{
public:
    void Init(Ref<RenderSystem> renderSystem, Ref<Camera> camera);
    void Begin(Ref<PointLight> light);
    void Draw(Ref<Mesh> mesh);
private:
    Ref<PointLight> m_Light;
};

}

#endif
