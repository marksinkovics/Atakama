#ifndef WINDOW_H
#define WINDOW_H

#include "Events/Event.hpp"
#include "Platform/GraphicsContext.hpp"

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
    float GetFrameBufferWidth();
    float GetFrameBufferHeight();

    float GetRatio();

    glm::vec2 GetSize();

    typedef std::function<void(Event&)> EventCallbackFunc;
    
    
    void SetEventCallback(const EventCallbackFunc& callback);

    void SwapBuffers();
    void PollEvents();
    
private:
    uint32_t m_Width;
    uint32_t m_Height;

    uint32_t m_FrameBufferWidth;
    uint32_t m_FrameBufferHeight;

    std::string m_Name;
    
    Ref<GraphicsContext> m_GraphicsContext;
    
    GLFWwindow* m_Window;
    EventCallbackFunc m_EventCallback;
};

}


#endif
