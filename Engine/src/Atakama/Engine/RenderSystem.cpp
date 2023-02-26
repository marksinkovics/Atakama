#include "RenderSystem.hpp"
#include "Atakama/Engine/VertexBuffer.hpp"

#include "OpenGL3/OpenGL3RenderSystem.hpp"

#include "Atakama/Scene/Entity.hpp"
#include "Atakama/Scene/Components/Components.hpp"
#include "Atakama/Scene/Components/TransformComponent.hpp"
#include "Atakama/Engine/Shader.hpp"

namespace Atakama
{

Ref<RenderSystem> RenderSystem::Create()
{
    switch(g_RuntimeGlobalContext.m_GraphicsAPI)
    {
        case GraphicsAPI::None:
        {
            LOG_FATAL("GraphicsAPI::None is not supported!");
            break;
        }
        case GraphicsAPI::OpenGL3: return CreateRef<OpenGL3RenderSystem>();
    }
}

void RenderSystem::Draw(Entity& entity, Ref<Shader>& shader)
{
    glm::mat4 modelMatrix {1.f};
    for (TransformComponent transform : entity.GetAncestorComponents<TransformComponent>())
    {
        modelMatrix = modelMatrix * transform.GetMat4();
    }

    shader->SetUniformMat4("uModel", modelMatrix);

    glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(modelMatrix));
    shader->SetUniformMat3("uNormalMatrix", normalMatrix);

    shader->SetUniformInt("u_MeshId", (uint32_t)entity);

    if (!entity.HasComponent<TextureComponent>())
    {
        shader->SetUniformInt("uHasTexture", 0);
    }
    else
    {
        TextureComponent& texture = entity.GetComponent<TextureComponent>();

        shader->SetUniformInt("uHasTexture", 1);
        texture.Texture->Bind(0);
        shader->SetUniformInt("textureSampler", 0);
    }

    MeshComponent& mesh = entity.GetComponent<MeshComponent>();
    Draw(mesh.Mesh->GetMode(), mesh.Mesh->GetVertexArray());

    if (entity.HasComponent<TextureComponent>())
    {
        TextureComponent& texture = entity.GetComponent<TextureComponent>();
        texture.Texture->Unbind();
    }
}

}

