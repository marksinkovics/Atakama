#ifndef ATAKAMA_LIGHTING_RENDERER_HPP
#define ATAKAMA_LIGHTING_RENDERER_HPP

#include "Renderer/Renderer.hpp"
#include "Engine/Mesh.hpp"
#include "Engine/Lights/PointLight.hpp"

namespace Atakama
{

class LightingRenderer: public Renderer
{
public:
    LightingRenderer(Ref<RenderSystem> renderSystem, Ref<Camera>& camera);
    void Begin(Ref<PointLight> light);
    void Draw(Ref<Mesh> mesh);
private:
    Ref<PointLight> m_Light;
};

}

#endif
