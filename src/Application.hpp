#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Camera.hpp"
#include "Window.hpp"
#include "Events/Event.hpp"
#include "Events/EventDispatcher.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"

#include <stdint.h>

namespace OGLSample
{

  class Application
  {
  public:
    static constexpr uint32_t WIDTH = 1024;
    static constexpr uint32_t HEIGHT = 768;

    Application();
    ~Application();

    void OnEvent(Event &event);
    bool OnKeyPressed(KeyPressedEvent &event);
    bool OnMouseButtonPressed(MouseButtonPressedEvent &event);
    bool OnMouseButtonReleased(MouseButtonReleasedEvent &event);
    bool OnMouseMoved(MouseMovedEvent &event);

    Application(const Application &) = delete;
    Application &operator=(const Application &) = delete;

    void run();

  private:

    Ref<Window> m_Window;
    Ref<Camera> m_Camera;
  };

}

#endif
