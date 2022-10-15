#ifndef SIMPLE_RENDERER_HPP
#define SIMPLE_RENDERER_HPP

#include "Renderer/Renderer.hpp"

namespace OGLSample
{

class SimpleRenderer: public Renderer
{
public:
    void Init(Ref<Camera> camera);
    void Draw(Ref<Model> model);
};

}

#endif
