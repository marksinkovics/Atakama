#include "DepthViewRenderPass.hpp"

#include <Atakama/Core/FileSystem.hpp>

#include "Atakama/Engine/AssetManager.hpp"
#include "Atakama/Engine/Shader.hpp"
#include "Atakama/Engine/RenderSystem.hpp"

namespace Atakama
{


DepthViewRenderPass::DepthViewRenderPass(Ref<RenderSystem> renderSystem)
: RenderPass(renderSystem)
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    AssetManager::Get()->LoadQuad(vertices, indices);
    m_Mesh = CreateRef<MeshObject>(vertices, indices);
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

    inputTexture->Bind(0);
    m_Shader->SetUniformInt("textureSampler", 0);
    m_RenderSystem->Draw(m_Mesh->GetMode(), m_Mesh->GetVertexArray());
    inputTexture->Unbind();
    m_Shader->Unbind();
}

}
