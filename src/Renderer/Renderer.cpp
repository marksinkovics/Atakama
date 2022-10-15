#include "Renderer.hpp"

namespace OGLSample
{

void Renderer::Init(Ref<Camera> camera, Ref<Shader> shader)
{
    m_Camera = camera;
    m_Shader = shader;
}

void Renderer::Begin()
{
    m_Shader->Bind();
}

void Renderer::Draw()
{

}

void Renderer::End()
{
    m_Shader->Unbind();
}

}
