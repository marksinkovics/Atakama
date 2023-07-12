#ifndef ATAKAMA_ASSIMP_IMPORTER_HPP
#define ATAKAMA_ASSIMP_IMPORTER_HPP

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Atakama
{

class Mesh;
class Texture;

class AssimpImporter
{
public:
    AssimpImporter(std::filesystem::path& path);

    bool Import();
private:
    void ProcessNode(aiNode* node);
    void ProcessMesh(aiMesh* mesh);
    std::vector<std::string> LoadMaterials(aiMaterial* material, aiTextureType type, std::string typeName);
public:
    std::vector<Ref<Mesh>>& GetMeshes() { return m_Meshes; }
    std::map<std::string, Ref<Texture>>& GetTextures() { return m_Textures; }
private:
    std::filesystem::path& m_Path;
    uint32_t m_ImportFlags = aiProcess_FlipUVs | aiProcess_Triangulate;
    std::vector<Ref<Mesh>> m_Meshes;
    std::map<std::string, Ref<Texture>> m_Textures;
    const aiScene* m_Scene = nullptr;
};

};


#endif