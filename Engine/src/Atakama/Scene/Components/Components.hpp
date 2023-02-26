
#ifndef ATAKAMA_ENGINE_COMPONENTS_HPP
#define ATAKAMA_ENGINE_COMPONENTS_HPP

#include "Atakama/Engine/Camera.hpp"
#include "Atakama/Engine/MeshObject.hpp"
#include "Atakama/Engine/Texture.hpp"

#include <entt/entt.hpp>

namespace Atakama
{

struct Parent
{
    entt::entity Parent { entt::null };
};

struct Children
{
    std::set<entt::entity> Children;
};


struct NameComponent
{
    std::string Name;
    NameComponent() = default;
    NameComponent(const NameComponent&) = default;
    NameComponent(const std::string& name): Name(name) {}
};

struct CameraComponent
{
    Camera Camera;
    bool Primary = false;
    CameraComponent(Camera::Mode mode): Mode(mode) { Camera.SetMode(mode); };
    Camera::Mode Mode { Camera::Mode::Perspective };
};

struct PointLightComponent
{
    glm::vec4 Color;
};

struct MeshObjectComponent
{
    Ref<MeshObject> Mesh;
};

struct DebugComponent
{
    int i;
};

struct TextureComponent
{
    Ref<Texture> Texture;
};

struct SkyBoxComponent
{
    int i;
};

}


#endif
