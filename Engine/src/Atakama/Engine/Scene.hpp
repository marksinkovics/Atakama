#ifndef ATAKAMA_SCENE_HPP
#define ATAKAMA_SCENE_HPP

#include "Shader.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"
#include "Atakama/Engine/Lights/PointLight.hpp"

#include <map>

namespace Atakama
{

class Scene
{
public:
    Scene() = default;
    virtual ~Scene() = default;
    
    virtual void Init();
    virtual void LoadLight();
    virtual void LoadTextures();
    virtual void LoadMeshes();
    
    Ref<PointLight> GetLight() const;

    Ref<Texture> GetTextureById(const std::string& id) const;
    
    std::vector<Ref<Mesh>> GetMeshes() const;
    std::vector<Ref<Mesh>>::iterator begin() { return m_Meshes.begin(); }
    std::vector<Ref<Mesh>>::iterator end() { return m_Meshes.end(); }
    std::vector<Ref<Mesh>>::const_iterator begin() const { return m_Meshes.begin(); }
    std::vector<Ref<Mesh>>::const_iterator end() const { return m_Meshes.end(); }
protected:
    std::map<std::string, Ref<Texture>> m_Textures;
    std::vector<Ref<Mesh>> m_Meshes;
    Ref<PointLight> m_PointLight;
};

class SandboxScene: public Scene
{
public:
    SandboxScene() = default;
    virtual ~SandboxScene() = default;
    virtual void LoadLight() override;
    virtual void LoadTextures() override;
    virtual void LoadMeshes() override;

};

}


#endif
