#ifndef ATAKAMA_SIMPLE_RENDERER_HPP
#define ATAKAMA_SIMPLE_RENDERER_HPP

#include "Renderer/Renderer.hpp"
#include "Engine/Mesh.hpp"

namespace Atakama
{

class SimpleRenderer: public Renderer
{
public:
    SimpleRenderer(Ref<RenderSystem> renderSystem, Ref<Camera>& camera);
    void Draw(Ref<Mesh> mesh);
};

}

#endif
