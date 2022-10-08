#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Camera.hpp"
#include "Shader.hpp"
#include "Model.hpp"

namespace OGLSample
{

class Renderer
{
public:
    Renderer() {}

    virtual void Init(Ref<Camera> camera, Ref<Shader> shader)
    {
        m_Camera = camera;
        m_Shader = shader;
    }

    virtual ~Renderer() = default;

    virtual void Begin()
    {
        m_Shader->Bind();
    }

    virtual void Draw(Ref<Model> model) = 0;

    virtual void End()
    {
        m_Shader->Unbind();
    }

protected:
    Ref<Shader> m_Shader;
    Ref<Camera> m_Camera;
};

}

#endif