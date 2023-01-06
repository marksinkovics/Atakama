#include "SkyBoxRenderPass.hpp"

#include "Engine/RenderSystem.hpp"
#include "Engine/Texture.hpp"
#include "Engine/Shader.hpp"
#include "Engine/AssetManager.hpp"
#include "FileSystem.hpp"
#include "Engine/Camera.hpp"

namespace OGLSample
{

SkyBoxRenderPass::SkyBoxRenderPass(Ref<RenderSystem> renderSystem, Ref<Camera> camera)
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
    m_Mesh = AssetManager::LoadSkyBox();
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
    m_Shader->SetUniformFloat3("uViewPosition", m_Camera->GetPosition());

    m_Mesh->Draw(m_RenderSystem, m_Shader);

    m_Shader->Unbind();
    m_RenderSystem->SetDepthCompare(DepthCompare::Less);
}

std::string SkyBoxRenderPass::GetName()
{
    return "SkyBox Render Pass";
}


}
