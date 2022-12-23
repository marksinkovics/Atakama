#ifndef LIGHTING_RENDERER_HPP
#define LIGHTING_RENDERER_HPP

#include "Renderer/Renderer.hpp"
#include "Mesh.hpp"
#include "Lights/PointLight.hpp"

namespace OGLSample
{

class LightingRenderer: public Renderer
{
public:
    void Init(Ref<Camera> camera);
    void Begin(Ref<PointLight> light);
    void Draw(Ref<Mesh> mesh);
private:
    Ref<PointLight> m_Light;
};

}

#endif
