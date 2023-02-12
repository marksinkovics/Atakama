#include "MainRenderPass.hpp"
#include "Atakama/Engine/RenderSystem.hpp"
#include <Atakama/Core/FileSystem.hpp>
#include "Atakama/Engine/AssetManager.hpp"

#include "Atakama/Engine/Shader.hpp"

#include "Atakama/Scene/Scene.hpp"
#include "Atakama/Engine/Camera.hpp"
#include "Atakama/Scene/Entity.hpp"
#include "Atakama/Scene/Components/Components.hpp"


namespace Atakama
{

MainRenderPass::MainRenderPass(Ref<RenderSystem> renderSystem, Ref<Scene> scene)
: SceneRenderPass(renderSystem, scene)
{
    m_Shader = CreateRef<Shader>(FileSystem::GetShaderFile("lighting_shader.vert"), FileSystem::GetShaderFile("lighting_shader.frag"));
}

void MainRenderPass::Draw()
{
    Entity cameraEntity = m_Scene->GetPrimaryCameraEntity();
    Camera& camera = cameraEntity.GetComponent<CameraComponent>().Camera;
    auto& cameraTransform = cameraEntity.GetComponent<TransformComponent>();

    Entity lightEntity = m_Scene->GetLight();
    PointLightComponent& lightLightComponent = lightEntity.GetComponent<PointLightComponent>();
    TransformComponent& lightTransformComponent = lightEntity.GetComponent<TransformComponent>();
    MeshComponent& lightMeshComponent = lightEntity.GetComponent<MeshComponent>();

    m_RenderSystem->SetDepthTest(true);
    m_RenderSystem->SetClearColor({0.0f, 0.0f, 0.4f, 0.0f});
    m_RenderSystem->Clear();

    m_Shader->Bind();
    for(const auto& mesh : *m_Scene)
    {
        m_Shader->SetUniformMat4("uView", camera.GetViewMatrix(cameraTransform));
        m_Shader->SetUniformMat4("uProjection", camera.GetProjectionMatrix());

        // Lights
        m_Shader->SetUniformFloat4("uLightPosition", glm::vec4(lightTransformComponent.Translate, 1.0f));
        m_Shader->SetUniformFloat4("uLightColor", lightLightComponent.Color);
        // Camera / View
        m_Shader->SetUniformFloat3("uViewPosition", cameraTransform.Translate);
        // Mesh
        m_Shader->SetUniformInt("u_SelectedMeshId", AssetManager::Get()->GetSelectedMeshId());

        mesh->Draw(m_RenderSystem, m_Shader);
    }
    m_Shader->Unbind();
}

std::string MainRenderPass::GetName()
{
    return "Main RenderPass";
}

}
