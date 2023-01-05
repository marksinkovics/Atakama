#include "ViewportRenderPass.hpp"

#include "FileSystem.hpp"

#include "Engine/AssetManager.hpp"
#include "Engine/Shader.hpp"
#include "Engine/Mesh.hpp"
#include "Engine/RenderSystem.hpp"

namespace OGLSample
{


ViewportRenderPass::ViewportRenderPass(Ref<RenderSystem> renderSystem)
: RenderPass(renderSystem)
{
    m_FrameBuffer = nullptr;
    m_Mesh = AssetManager::LoadQuad();
    m_Shader = CreateRef<Shader>(FileSystem::GetShaderFile("viewport.vert"), FileSystem::GetShaderFile("viewport.frag"));
}

ViewportRenderPass::~ViewportRenderPass()
{
    m_Mesh.reset();
    m_Shader->Unbind();
    m_Shader.reset();
}

void ViewportRenderPass::Draw()
{
    if (m_Dependencies.size() == 0)
        return;

    Ref<RenderPass> inputRenderPass = m_Dependencies[0];

    if (!inputRenderPass)
        return;

    Ref<Texture> inputTexture = inputRenderPass->GetOutputColorTexture();

    if (!inputTexture)
        return;

    m_RenderSystem->SetDepthTest(false);
    m_RenderSystem->SetClearColor({1.0f, 1.0f, 1.0f, 0.0f});
    m_RenderSystem->Clear();

    m_Shader->Bind();
    m_Mesh->GetSubMeshes()[0]->SetTexture(inputTexture);
    m_Mesh->Draw(m_RenderSystem, m_Shader);
    m_Shader->Unbind();
}

}