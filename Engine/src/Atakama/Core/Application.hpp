#ifndef ATAKAMA_APPLICATION_HPP
#define ATAKAMA_APPLICATION_HPP

#include "Atakama/Core/Window.hpp"
#include "Atakama/Events/Event.hpp"
#include "Atakama/Events/KeyEvent.hpp"
#include "Atakama/Events/MouseEvent.hpp"

#include "Atakama/Engine/Engine.hpp"

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
