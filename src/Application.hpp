#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Window.hpp"
#include "Events/Event.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"

#include "Engine/Engine.hpp"

#include <stdint.h>

namespace OGLSample
{

  class Application
  {
  public:
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
    Ref<Engine> m_Engine;
  };

}

#endif
