#ifndef TEXTURE_RENDERER_HPP
#define TEXTURE_RENDERER_HPP

#include "Renderer/Renderer.hpp"

namespace OGLSample
{

class TextureRenderer: public Renderer
{
public:
    void Init(Ref<Camera> camera);
    virtual void Draw(Ref<Model> model);
};

}

#endif
