#ifndef ATAKAMA_APPLICATION_HPP
#define ATAKAMA_APPLICATION_HPP

#include "Window.hpp"
#include "Events/Event.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"

#include "Engine/Engine.hpp"

#include <stdint.h>

namespace Atakama
{

class Application
{
public:
    Application();
    ~Application();

    void OnEvent(Event &event);
    bool OnMouseButtonPressed(MouseButtonPressedEvent &event);

    void BlockEvent(bool value);

    Application(const Application &) = delete;
    Application &operator=(const Application &) = delete;

    void run();
private:
    Ref<Window> m_Window;
    Ref<Engine> m_Engine;
    bool m_BlockEvents;
};

}

#endif
