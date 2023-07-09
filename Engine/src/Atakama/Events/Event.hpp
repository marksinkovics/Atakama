#ifndef ATAKAMA_EVENT_HPP
#define ATAKAMA_EVENT_HPP

namespace Atakama
{

enum class EventType
{
    None,
    WindowClose, WindowResize, WindowFrameBufferResize,
    MouseMoved, MouseButtonPressed, MouseButtonReleased, MouseScrolled, MouseEnter, MouseLeave,
    KeyPressed, KeyReleased, KeyTyped,
    Drop
};

#define EVENT_PROPERTIES(Type) \
    virtual EventType GetType() const override { return Type; } \
    static EventType GetStaticType() { return Type; } \
    virtual const char* GetName() const override { return #Type; };

class Event
{
public:
    Event() = default;
    virtual EventType GetType() const = 0;
    virtual const char* GetName() const = 0;
    bool Handled = false;
};

bool IsKeyboardEvent(Event& event);
bool IsMouseEvent(Event& event);

}

#endif
