#ifndef POINTLIGHT_RENDERER_HPP
#define POINTLIGHT_RENDERER_HPP

#include "Renderer/Renderer.hpp"
#include "Mesh.hpp"

namespace OGLSample
{

class PointLightRenderer: public Renderer
{
public:
    void Init(Ref<Camera> camera);
    virtual void Draw(glm::vec4 lightPosition, glm::vec4 lightColor);
private:
    Ref<Mesh> m_LightMesh = nullptr;
};

}

#endif
