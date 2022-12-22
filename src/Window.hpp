#ifndef WINDOW_H
#define WINDOW_H

#include "Events/Event.hpp"

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

    bool ShouldClose();

    GLFWwindow* GetWindow() const;

    float GetWidth();
    float GetHeight();
    float GetRatio();

    glm::vec2 GetSize();

    typedef std::function<void(Event&)> EventCallbackFunc;
    
    
    void SetEventCallback(const EventCallbackFunc& callback);

    void SwapBuffers();
    void PollEvents();
    
private:
    uint32_t m_Width;
    uint32_t m_Height;
    std::string m_Name;
    GLFWwindow* m_Window;
    EventCallbackFunc m_EventCallback;
};

}


#endif
