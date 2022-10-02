#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace OGLSample {

class Window
{
public:
    Window(uint32_t width, uint32_t height, const std::string& name);
    ~Window();

    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;

    bool shouldClose();

    GLFWwindow* GetWindow() const;

    float GetWidth();
    float GetHeight();
    float GetRatio();

private:
    uint32_t m_Width;
    uint32_t m_Height;
    std::string m_Name;
    GLFWwindow* m_Window;
};

}


#endif
