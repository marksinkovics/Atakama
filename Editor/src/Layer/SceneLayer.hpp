#ifndef ATAKAMA_EDITOR_SCENE_LAYER_HPP
#define ATAKAMA_EDITOR_SCENE_LAYER_HPP

#include <Atakama/Core/Layer.hpp>

namespace Atakama
{

class Engine;
class Scene;

namespace Editor
{

class SceneLayer: public Layer
{
public:
    SceneLayer();
    virtual ~SceneLayer() = default;
    virtual void OnUpdateUI(float ts) override;
private:
    Ref<Engine> m_Engine;
    Ref<Scene> m_Scene;
};

}

}

#endif /* SceneLayer_hpp */
