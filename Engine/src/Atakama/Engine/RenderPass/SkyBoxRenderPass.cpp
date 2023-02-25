#include "SkyBoxRenderPass.hpp"

#include "Atakama/Engine/RenderSystem.hpp"
#include "Atakama/Engine/Shader.hpp"
#include "Atakama/Engine/AssetManager.hpp"
#include "Atakama/Core/FileSystem.hpp"

#include "Atakama/Scene/Scene.hpp"
#include "Atakama/Engine/Camera.hpp"
#include "Atakama/Scene/Entity.hpp"
#include "Atakama/Scene/Components/Components.hpp"

namespace Atakama
{

SkyBoxRenderPass::SkyBoxRenderPass(Ref<RenderSystem> renderSystem, Ref<Scene>& scene)
: RenderPass(renderSystem), m_Scene(scene)
{
    m_Shader = CreateRef<Shader>(FileSystem::GetShaderFile("skybox.vert"), FileSystem::GetShaderFile("skybox.frag"));
}

void SkyBoxRenderPass::Draw()
{
    Entity cameraEntity = m_Scene->GetPrimaryCameraEntity();
    Camera& camera = cameraEntity.GetComponent<CameraComponent>().Camera;
    auto& transform = cameraEntity.GetComponent<TransformComponent>();

    Entity skyBoxEntity = m_Scene->GetSkyBox();

    m_RenderSystem->SetDepthCompare(DepthCompare::LessOrEqual);

    m_Shader->Bind();

    // remove translation from the view matrix
    m_Shader->SetUniformMat4("uView", glm::mat4(glm::mat3(camera.GetViewMatrix(transform))));
    m_Shader->SetUniformMat4("uProjection", camera.GetProjectionMatrix());
    // Camera / View
    m_Shader->SetUniformFloat3("uViewPosition", transform.Translate);

    m_RenderSystem->Draw(skyBoxEntity, m_Shader);

    m_Shader->Unbind();
    m_RenderSystem->SetDepthCompare(DepthCompare::Less);
}

std::string SkyBoxRenderPass::GetName()
{
    return "SkyBox Render Pass";
}


}
