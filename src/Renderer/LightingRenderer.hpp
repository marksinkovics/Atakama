#ifndef LIGHTING_RENDERER_HPP
#define LIGHTING_RENDERER_HPP

#include "Renderer/Renderer.hpp"
#include "Mesh.hpp"

namespace OGLSample
{

class LightingRenderer: public Renderer
{
public:
    void Init(Ref<Camera> camera);
    void Begin(glm::vec4 lightPosition, glm::vec4 lightColor);
    void Draw(Ref<Mesh> mesh);
private:
    glm::vec4 m_LightPosition;
    glm::vec4 m_LightColor;
};

}

#endif
