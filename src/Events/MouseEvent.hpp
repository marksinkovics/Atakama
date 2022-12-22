#ifndef MOUSE_EVENT_HPP
#define MOUSE_EVENT_HPP

#include "Events/Event.hpp"

namespace OGLSample
{

class MouseButtonEvent: public Event
{
public:
    MouseButtonEvent(int button, EventType type, const std::string &name = ""): Event(type, name), m_Button(button) {}
    virtual int GetButton() const { return m_Button; }
protected:
    int m_Button;
};

class MouseButtonPressedEvent: public MouseButtonEvent
{
public:
    MouseButtonPressedEvent(int button, bool isRepeat = false) : MouseButtonEvent(button, EventType::MouseButtonPressed, "KeyPressedEvent") {}
    virtual ~MouseButtonPressedEvent() = default;
};

class MouseButtonReleasedEvent: public MouseButtonEvent
{
public:
    MouseButtonReleasedEvent(int button, bool isRepeat = false) : MouseButtonEvent(button, EventType::MouseButtonReleased, "KeyReleasedEvent") {}
    virtual ~MouseButtonReleasedEvent() = default;
};

class MouseScrolledEvent: public Event
{
public:
    MouseScrolledEvent(double xOffset, double yOffset): Event(EventType::MouseScrolled, "MouseScrolledEvent"), m_XOffset(xOffset), m_YOffset(yOffset) {}
    virtual ~MouseScrolledEvent() = default;
    virtual int GetXOffset() const { return m_XOffset; }
    virtual int GetYOffset() const { return m_YOffset; }
protected:
    double m_XOffset;
    double m_YOffset;
};

class MouseMovedEvent: public Event
{
public:
    MouseMovedEvent(double xPos, double yPos): Event(EventType::MouseMoved, "MouseMovedEvent"), m_XPos(xPos), m_YPos(yPos) {}
    virtual ~MouseMovedEvent() = default;
    virtual double GetXPos() const { return m_XPos; }
    virtual double GetYPos() const { return m_YPos; }
    virtual glm::dvec2 GetPos() const { return {m_XPos, m_YPos}; }
protected:
    double m_XPos;
    double m_YPos;
};

}

#endif
