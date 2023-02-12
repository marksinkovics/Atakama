#include "DepthViewRenderPass.hpp"

#include <Atakama/Core/FileSystem.hpp>

#include "Atakama/Engine/AssetManager.hpp"
#include "Atakama/Engine/Shader.hpp"
#include "Atakama/Engine/Mesh.hpp"
#include "Atakama/Engine/RenderSystem.hpp"

namespace Atakama
{


DepthViewRenderPass::DepthViewRenderPass(Ref<RenderSystem> renderSystem)
: RenderPass(renderSystem)
{
    m_Mesh = AssetManager::Get()->LoadQuad();
    m_Shader = CreateRef<Shader>(FileSystem::GetShaderFile("screen_depth_shader.vert"), FileSystem::GetShaderFile("screen_depth_shader.frag"));
}

DepthViewRenderPass::~DepthViewRenderPass()
{
    m_Mesh.reset();
    m_Shader->Unbind();
    m_Shader.reset();
}

void DepthViewRenderPass::Draw()
{
    if (m_Dependencies.size() == 0)
        return;

    Ref<RenderPass> inputRenderPass = m_Dependencies[0];

    if (!inputRenderPass)
        return;

    Ref<Texture> inputTexture = inputRenderPass->GetOutputDepthTexture();

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