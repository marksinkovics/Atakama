#include "SkyBoxRenderPass.hpp"

#include "Atakama/Engine/RenderSystem.hpp"
#include "Atakama/Engine/Texture.hpp"
#include "Atakama/Engine/Shader.hpp"
#include "Atakama/Engine/AssetManager.hpp"
#include <Atakama/Core/FileSystem.hpp>
#include "Atakama/Engine/Camera.hpp"

namespace Atakama
{

SkyBoxRenderPass::SkyBoxRenderPass(Ref<RenderSystem> renderSystem, Ref<Camera>& camera)
: RenderPass(renderSystem), m_Camera(camera)
{
    std::filesystem::path path = FileSystem::GetTexturePath();
    m_Texture = TextureCube::Create({
        FileSystem::GetTexturePath() / "right.jpg",
        FileSystem::GetTexturePath() / "left.jpg",
        FileSystem::GetTexturePath() / "top.jpg",
        FileSystem::GetTexturePath() / "bottom.jpg",
        FileSystem::GetTexturePath() / "front.jpg",
        FileSystem::GetTexturePath() / "back.jpg"
    });

    m_Shader = CreateRef<Shader>(FileSystem::GetShaderFile("skybox.vert"), FileSystem::GetShaderFile("skybox.frag"));
    m_Mesh = AssetManager::Get()->LoadSkyBox();
    m_Mesh->GetSubMeshes()[0]->SetTexture(m_Texture);
}

void SkyBoxRenderPass::Draw()
{
    m_RenderSystem->SetDepthCompare(DepthCompare::LessOrEqual);

    m_Shader->Bind();

    // remove translation from the view matrix
    m_Shader->SetUniformMat4("uView", glm::mat4(glm::mat3(m_Camera->GetViewMatrix())));
    m_Shader->SetUniformMat4("uProjection", m_Camera->GetProjectionMatrix());
    // Camera / View
    m_Shader->SetUniformFloat3("uViewPosition", m_Camera->Transform.Translate);

    m_Mesh->Draw(m_RenderSystem, m_Shader);

    m_Shader->Unbind();
    m_RenderSystem->SetDepthCompare(DepthCompare::Less);
}

std::string SkyBoxRenderPass::GetName()
{
    return "SkyBox Render Pass";
}


}
