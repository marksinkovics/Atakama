
#include "AssimpImporter.hpp"

#include <Atakama/Engine/Vertex.hpp>
#include <Atakama/Engine/Mesh.hpp>
#include <Atakama/Engine/Texture.hpp>

#include <sstream>

namespace Atakama
{
	
AssimpImporter::AssimpImporter(std::filesystem::path& path) : m_Path(path) {}

bool AssimpImporter::Import() {
    Assimp::Importer importer;
    m_Scene = importer.ReadFile(m_Path.string(), m_ImportFlags);
    if (!m_Scene || m_Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !m_Scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return false;
    }

    ProcessNode(m_Scene->mRootNode);
    return true;
}
    
void AssimpImporter::ProcessNode(aiNode* node)
{
    LOG_DEBUG("Process node: {}", (void*)node);
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = m_Scene->mMeshes[node->mMeshes[i]];
        ProcessMesh(mesh);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i]);
    }
}
    
void AssimpImporter::ProcessMesh(aiMesh* mesh)
{
    LOG_DEBUG("Process mesh: {}", (void*)mesh);
    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
    std::vector<Vertex> vertices;
    vertices.reserve(mesh->mNumVertices);

    for (uint32_t i = 0; i < mesh->mNumVertices; i++)
    {
        const aiVector3D* position = &(mesh->mVertices[i]);
        const aiVector3D* normal = &(mesh->mNormals[i]);
        const aiVector3D* uv = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &Zero3D;
        Vertex vertex;
        vertex.position = glm::vec3(position->x, position->y, position->z);
        vertex.normal = glm::vec3(normal->x, normal->y, normal->z);
        vertex.uv = glm::vec2(uv->x, uv->y);
        vertices.push_back(std::move(vertex));
    }

    std::vector<uint32_t> indices;
    vertices.reserve(mesh->mNumFaces * 3);

    for (uint32_t i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace& face = mesh->mFaces[i];
        ASSERT(face.mNumIndices == 3 && "Face has more vertex than 3");
        indices.push_back(face.mIndices[0]);
        indices.push_back(face.mIndices[1]);
        indices.push_back(face.mIndices[2]);
    }

    aiMaterial* material = m_Scene->mMaterials[mesh->mMaterialIndex];
    std::vector<std::string> diffuseMapIds = LoadMaterials(material, aiTextureType_DIFFUSE, "texture_diffuse");
    Ref<Mesh> meshObject = CreateRef<Mesh>(vertices, indices);

    if (diffuseMapIds.size() > 0)
    {
        meshObject->SetTextureId(diffuseMapIds[0]);
    }
    m_Meshes.push_back(meshObject);
}
    
std::vector<std::string> AssimpImporter::LoadMaterials(aiMaterial* material, aiTextureType type, std::string typeName)
{
    LOG_DEBUG("Process material: {}", (void*)material);
    uint32_t textureCount = material->GetTextureCount(type);
    std::vector<std::string> textureIds;
    for (uint32_t i = 0; i < textureCount; i++)
    {
        aiString str;
        material->GetTexture(type, i, &str);
        std::stringstream stream(str.C_Str());
        std::string partialPath;
        std::filesystem::path texturePath = m_Path.parent_path();
        while (std::getline(stream, partialPath, '/'))
        {
            texturePath /= partialPath;
        }

        std::string textureId = texturePath.string();
        textureIds.push_back(textureId);
        if (!m_Textures.contains(textureId))
        {
            m_Textures[textureId] = Texture2D::Create(texturePath);
        }
    }

    return textureIds;
}

}
