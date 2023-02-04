#ifndef ATAKAMA_MOUSE_EVENT_HPP
#define ATAKAMA_MOUSE_EVENT_HPP

#include "Atakama/Events/Event.hpp"

namespace Atakama
{

class MouseButtonEvent: public Event
{
public:
    MouseButtonEvent(int button): m_Button(button) {}
    virtual int GetButton() const { return m_Button; }
protected:
    int m_Button;
};

class MouseButtonPressedEvent: public MouseButtonEvent
{
public:
    MouseButtonPressedEvent(int button, bool isRepeat = false) : MouseButtonEvent(button) {}
    virtual ~MouseButtonPressedEvent() = default;
    EVENT_PROPERTIES(EventType::MouseButtonPressed);
};

class MouseButtonReleasedEvent: public MouseButtonEvent
{
public:
    MouseButtonReleasedEvent(int button, bool isRepeat = false) : MouseButtonEvent(button) {}
    virtual ~MouseButtonReleasedEvent() = default;
    EVENT_PROPERTIES(EventType::MouseButtonReleased);
};

class MouseScrolledEvent: public Event
{
public:
    MouseScrolledEvent(double xOffset, double yOffset): m_XOffset(xOffset), m_YOffset(yOffset) {}
    virtual ~MouseScrolledEvent() = default;
    virtual int GetXOffset() const { return m_XOffset; }
    virtual int GetYOffset() const { return m_YOffset; }
    EVENT_PROPERTIES(EventType::MouseScrolled);
protected:
    double m_XOffset;
    double m_YOffset;
};

class MouseMovedEvent: public Event
{
public:
    MouseMovedEvent(double xPos, double yPos): m_XPos(xPos), m_YPos(yPos) {}
    virtual ~MouseMovedEvent() = default;
    virtual double GetXPos() const { return m_XPos; }
    virtual double GetYPos() const { return m_YPos; }
    virtual glm::dvec2 GetPos() const { return {m_XPos, m_YPos}; }
    EVENT_PROPERTIES(EventType::MouseMoved);
protected:
    double m_XPos;
    double m_YPos;
};

}

#endif
