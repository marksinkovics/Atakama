#include "Renderer.hpp"

namespace OGLSample
{

Renderer::Renderer(Ref<RenderSystem> renderSystem, Ref<Camera>& camera, Ref<Shader> shader)
: m_RenderSystem(renderSystem), m_Camera(camera), m_Shader(shader)
{
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
