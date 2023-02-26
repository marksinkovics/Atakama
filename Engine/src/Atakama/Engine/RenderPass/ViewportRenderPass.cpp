#include "ViewportRenderPass.hpp"

#include <Atakama/Core/FileSystem.hpp>

#include "Atakama/Engine/AssetManager.hpp"
#include "Atakama/Engine/Shader.hpp"
#include "Atakama/Engine/Mesh.hpp"
#include "Atakama/Engine/RenderSystem.hpp"

namespace Atakama
{


ViewportRenderPass::ViewportRenderPass(Ref<RenderSystem> renderSystem)
: RenderPass(renderSystem)
{
    m_FrameBuffer = nullptr;

    m_Mesh = AssetManager::Get()->GetMeshById("canvas");
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

    inputTexture->Bind(0);
    m_Shader->SetUniformInt("u_TextureSampler", 0);

    m_RenderSystem->Draw(m_Mesh->GetMode(), m_Mesh->GetVertexArray());

    inputTexture->Unbind();
    m_Shader->Unbind();
}

}
