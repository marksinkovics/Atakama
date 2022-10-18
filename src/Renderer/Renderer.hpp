#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Camera.hpp"
#include "Shader.hpp"
#include "SubMesh.hpp"

namespace OGLSample
{

class Renderer
{
public:
    Renderer() {}

    virtual void Init(Ref<Camera> camera, Ref<Shader> shader);
    virtual ~Renderer() = default;

    virtual void Begin();
    virtual void Draw();
    virtual void End();

protected:
    Ref<Shader> m_Shader;
    Ref<Camera> m_Camera;
};

}

#endif
