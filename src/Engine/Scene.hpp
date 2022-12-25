#ifndef SCENE_HPP
#define SCENE_HPP

#include "Shader.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"
#include "Engine/Lights/PointLight.hpp"

#include <map>

namespace OGLSample
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
    Ref<Mesh> GetModelById(const std::string& id) const;
protected:
    std::map<std::string, Ref<Texture>> m_Textures;
    std::map<std::string, Ref<Mesh>> m_Meshes;
    
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
