#ifndef OPENGL3_GRAPHICS_CONTEXT_HPP
#define OPENGL3_GRAPHICS_CONTEXT_HPP

#include "Platform/GraphicsContext.hpp"

class GLFWwindow;

namespace OGLSample
{

class OpenGL3GraphicsContext: public GraphicsContext
{
public:
    virtual void Init() override;
    virtual void Register(void *window) override;
    virtual void SwapBuffers() override;
private:
    GLFWwindow* m_Window;
};

}

#endif
