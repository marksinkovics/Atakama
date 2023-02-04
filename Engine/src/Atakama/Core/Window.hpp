#ifndef ATAKAMA_WINDOW_HPP
#define ATAKAMA_WINDOW_HPP

#include "Atakama/Events/Event.hpp"
#include "Atakama/Engine/Platform/GraphicsContext.hpp"

#include <string>

class GLFWwindow;

namespace Atakama {

class Window
{
public:
    Window(uint32_t width, uint32_t height, const std::string& name);
    ~Window();

    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;

    bool ShouldClose();

    GLFWwindow* GetWindow() const;

    uint32_t GetWidth();
    uint32_t GetHeight();
    glm::uvec2 GetSize();
    uint32_t GetFrameBufferWidth();
    uint32_t GetFrameBufferHeight();
    glm::uvec2 GetFrameBufferSize();

    float GetRatio();

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
