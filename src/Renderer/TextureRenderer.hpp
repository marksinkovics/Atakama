#ifndef TEXTURE_RENDERER_HPP
#define TEXTURE_RENDERER_HPP

#include "Renderer/Renderer.hpp"
#include "Engine/Mesh.hpp"

namespace OGLSample
{

class TextureRenderer: public Renderer
{
public:
    void Init(Ref<RenderSystem> renderSystem, Ref<Camera> camera);
    void Draw(Ref<Mesh> mesh);
};

}

#endif
