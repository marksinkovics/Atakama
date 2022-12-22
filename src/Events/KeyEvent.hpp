#ifndef KEYEVENT_HPP
#define KEYEVENT_HPP

#include "Events/Event.hpp"

namespace OGLSample
{

class KeyEvent: public Event
{
public:
    KeyEvent(int keyCode, EventType type, const std::string &name = ""): Event(type, name), m_KeyCode(keyCode) {}
    virtual int GetKeyCode() const { return m_KeyCode; }
protected:
    int m_KeyCode;
};

class KeyPressedEvent: public KeyEvent
{
public:
    KeyPressedEvent(int keyCode, bool isRepeat = false) : KeyEvent(keyCode, EventType::KeyPressed, "KeyPressedEvent"), m_IsRepeat(isRepeat) {}
    virtual ~KeyPressedEvent() = default;
private:
    bool m_IsRepeat;
};

class KeyReleasedEvent: public KeyEvent
{
public:
    KeyReleasedEvent(int keyCode, bool isRepeat = false) : KeyEvent(keyCode, EventType::KeyReleased, "KeyReleasedEvent"), m_IsRepeat(isRepeat) {}
    virtual ~KeyReleasedEvent() = default;
private:
    bool m_IsRepeat;
};


}

#endif
