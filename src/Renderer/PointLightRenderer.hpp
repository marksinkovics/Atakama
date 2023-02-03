#ifndef ATAKAMA_POINTLIGHT_RENDERER_HPP
#define ATAKAMA_POINTLIGHT_RENDERER_HPP

#include "Renderer/Renderer.hpp"
#include "Engine/Lights/PointLight.hpp"

namespace Atakama
{

class PointLightRenderer: public Renderer
{
public:
    PointLightRenderer(Ref<RenderSystem> renderSystem, Ref<Camera>& camera);
    virtual void Draw(Ref<PointLight> light);
};

}

#endif
