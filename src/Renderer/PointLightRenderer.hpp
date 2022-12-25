#ifndef POINTLIGHT_RENDERER_HPP
#define POINTLIGHT_RENDERER_HPP

#include "Renderer/Renderer.hpp"
#include "Engine/Lights/PointLight.hpp"

namespace OGLSample
{

class PointLightRenderer: public Renderer
{
public:
    void Init(Ref<RenderSystem> renderSystem, Ref<Camera> camera);
    virtual void Draw(Ref<PointLight> light);
};

}

#endif
