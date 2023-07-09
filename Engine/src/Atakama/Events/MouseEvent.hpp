#ifndef ATAKAMA_MOUSE_EVENT_HPP
#define ATAKAMA_MOUSE_EVENT_HPP

#include "Atakama/Events/Event.hpp"

namespace Atakama
{

class MouseEvent : public Event 
{
};

class MouseButtonEvent: public MouseEvent
{
public:
    MouseButtonEvent(int button, double xPos, double yPos, int mods): MouseEvent(), m_Button(button), m_XPos(xPos), m_YPos(yPos), m_Mods(mods) {}
    virtual int GetButton() const { return m_Button; }
    virtual double GetXPos() const { return m_XPos; }
    virtual double GetYPos() const { return m_YPos; }
    virtual glm::dvec2 GetPos() const { return { m_XPos, m_YPos }; }
protected:
    int m_Button;
    double m_XPos;
    double m_YPos;
    int m_Mods;
};

class MouseButtonPressedEvent: public MouseButtonEvent
{
public:
    MouseButtonPressedEvent(int button, double xPos, double yPos, int mods) : MouseButtonEvent(button, xPos, yPos, mods) {}
    virtual ~MouseButtonPressedEvent() = default;
    EVENT_PROPERTIES(EventType::MouseButtonPressed);
};

class MouseButtonReleasedEvent: public MouseButtonEvent
{
public:
    MouseButtonReleasedEvent(int button, double xPos, double yPos, int mods) : MouseButtonEvent(button, xPos, yPos, mods) {}
    virtual ~MouseButtonReleasedEvent() = default;
    EVENT_PROPERTIES(EventType::MouseButtonReleased);
};

class MouseScrolledEvent: public MouseEvent
{
public:
    MouseScrolledEvent(double xOffset, double yOffset): m_XOffset(xOffset), m_YOffset(yOffset) {}
    virtual ~MouseScrolledEvent() = default;
    virtual int GetXOffset() const { return m_XOffset; }
    virtual int GetYOffset() const { return m_YOffset; }
    virtual glm::dvec2 GetOffset() const { return { m_XOffset, m_YOffset }; }
    EVENT_PROPERTIES(EventType::MouseScrolled);
protected:
    double m_XOffset;
    double m_YOffset;
};

class MouseMovedEvent: public MouseEvent
{
public:
    MouseMovedEvent(double xPos, double yPos): MouseEvent(), m_XPos(xPos), m_YPos(yPos) {}
    virtual ~MouseMovedEvent() = default;
    virtual double GetXPos() const { return m_XPos; }
    virtual double GetYPos() const { return m_YPos; }
    virtual glm::dvec2 GetPos() const { return {m_XPos, m_YPos}; }
    EVENT_PROPERTIES(EventType::MouseMoved);
protected:
    double m_XPos;
    double m_YPos;
};


class MouseEnterEvent : public MouseEvent
{
public:
    MouseEnterEvent() {}
    virtual ~MouseEnterEvent() = default;
    EVENT_PROPERTIES(EventType::MouseEnter);
};

class MouseLeaveEvent : public MouseEvent
{
public:
    MouseLeaveEvent() {}
    virtual ~MouseLeaveEvent() = default;
    EVENT_PROPERTIES(EventType::MouseLeave);
};


}

#endif
