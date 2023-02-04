#ifndef ATAKAMA_OPENGL3_GRAPHICS_CONTEXT_HPP
#define ATAKAMA_OPENGL3_GRAPHICS_CONTEXT_HPP

#include "Atakama/Engine/Platform/GraphicsContext.hpp"

class GLFWwindow;

namespace Atakama
{

class OpenGL3GraphicsContext: public GraphicsContext
{
public:
    virtual void Init() override;
    virtual void Register(void *window) override;
    virtual void SwapBuffers() override;
    virtual void SetVSync(bool enable) override;
    virtual bool GetVSync() const override;
private:
    GLFWwindow* m_Window;
    bool m_VSyncEnabled;
};

}

#endif
