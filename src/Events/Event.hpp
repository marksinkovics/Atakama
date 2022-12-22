#ifndef EVENT_HPP
#define EVENT_HPP

#include <array>

namespace OGLSample
{

enum class EventType
{
    None,
    WindowClose, WindowResize,
    MouseMoved, MouseButtonPressed, MouseButtonReleased, MouseScrolled,
    KeyPressed, KeyReleased, KeyTyped
};

class Event
{
protected:
    EventType m_Type;
    std::string m_Name;
public:
    Event() = default;
    Event(EventType type, const std::string &name = "") : m_Type(type), m_Name(name) {}
    inline const EventType GetType() const { return m_Type; }
    inline const std::string &GetName() const { return m_Name; }
    
    bool Handled = false;
};

bool IsKeyboardEvent(Event& event);
bool IsMouseEvent(Event& event);

}

#endif
