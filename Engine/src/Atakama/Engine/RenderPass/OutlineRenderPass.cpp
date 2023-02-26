#include "OutlineRenderPass.hpp"

#include <Atakama/Core/FileSystem.hpp>

#include "Atakama/Engine/AssetManager.hpp"
#include "Atakama/Engine/Shader.hpp"
#include "Atakama/Engine/RenderSystem.hpp"
#include "Atakama/Engine/FrameBuffer.hpp"

namespace Atakama
{


OutlineRenderPass::OutlineRenderPass(Ref<RenderSystem> renderSystem)
: RenderPass(renderSystem)
{
    m_Mesh = AssetManager::Get()->GetMeshById("canvas");
    m_Shader = CreateRef<Shader>(FileSystem::GetShaderFile("outline.vert"), FileSystem::GetShaderFile("outline.frag"));
}

OutlineRenderPass::~OutlineRenderPass()
{
    m_Mesh.reset();
    m_Shader->Unbind();
    m_Shader.reset();
}

void OutlineRenderPass::Draw()
{
    if (m_Dependencies.size() == 0)
        return;

    Ref<RenderPass> inputRenderPass = m_Dependencies[0];

    if (!inputRenderPass)
        return;

    Ref<Texture> inputTexture = inputRenderPass->GetOutputColorTexture();

    if (!inputTexture)
        return;

    Ref<Texture> meshTexture = inputRenderPass->GetOutputMeshTexture();

    if (!meshTexture)
        return;

    m_RenderSystem->SetDepthTest(false);
    m_RenderSystem->SetClearColor({1.0f, 1.0f, 1.0f, 0.0f});
    m_RenderSystem->Clear();

    m_Shader->Bind();

    m_Shader->SetUniformInt("u_SelectedMeshId", AssetManager::Get()->GetSelectedMeshId());

    m_Shader->SetUniformFloat2("u_TextureSize", glm::vec2(m_FrameBuffer->GetWidth(), m_FrameBuffer->GetHeight()));

    inputTexture->Bind(0);
    m_Shader->SetUniformInt("u_TextureSampler", 0);

    meshTexture->Bind(1);
    m_Shader->SetUniformInt("u_MeshIdSampler", 1);

    m_RenderSystem->Draw(m_Mesh->GetMode(), m_Mesh->GetVertexArray());
    m_Shader->Unbind();
}

}
