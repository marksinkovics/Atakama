#ifndef POINTLIGHT_RENDERER_HPP
#define POINTLIGHT_RENDERER_HPP

#include "Renderer/Renderer.hpp"
#include "Mesh.hpp"
#include "Lights/PointLight.hpp"

namespace OGLSample
{

class PointLightRenderer: public Renderer
{
public:
    void Init(Ref<Camera> camera);
    virtual void Draw(Ref<PointLight> light);
};

}

#endif
