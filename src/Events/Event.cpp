#include "Event.hpp"

namespace OGLSample
{



bool IsKeyboardEvent(Event& event)
{
    EventType type = event.GetType();
    if(type == EventType::KeyPressed)
        return true;
        
    if(type == EventType::KeyReleased)
        return true;

    if(type == EventType::KeyTyped)
        return true;

    return false;
}
        
        
bool IsMouseEvent(Event& event)
{
    EventType type = event.GetType();
    if(type == EventType::MouseMoved)
        return true;
        
    if(type == EventType::MouseScrolled)
        return true;

    if(type == EventType::MouseButtonPressed)
        return true;

    if(type == EventType::MouseButtonReleased)
        return true;

    return false;
}

}
