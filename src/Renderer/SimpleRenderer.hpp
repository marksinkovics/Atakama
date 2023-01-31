#ifndef SIMPLE_RENDERER_HPP
#define SIMPLE_RENDERER_HPP

#include "Renderer/Renderer.hpp"
#include "Engine/Mesh.hpp"

namespace OGLSample
{

class SimpleRenderer: public Renderer
{
public:
    SimpleRenderer(Ref<RenderSystem> renderSystem, Ref<Camera>& camera);
    void Draw(Ref<Mesh> mesh);
};

}

#endif
