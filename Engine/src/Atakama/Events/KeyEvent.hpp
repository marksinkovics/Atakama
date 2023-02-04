#ifndef ATAKAMA_KEYEVENT_HPP
#define ATAKAMA_KEYEVENT_HPP

#include "Atakama/Events/Event.hpp"

namespace Atakama
{

class KeyEvent: public Event
{
public:
    KeyEvent(int keyCode): m_KeyCode(keyCode) {}
    virtual int GetKeyCode() const { return m_KeyCode; }
protected:
    int m_KeyCode;
};

class KeyPressedEvent: public KeyEvent
{
public:
    KeyPressedEvent(int keyCode, bool isRepeat = false) : KeyEvent(keyCode), m_IsRepeat(isRepeat) {}
    virtual ~KeyPressedEvent() = default;
    EVENT_PROPERTIES(EventType::KeyPressed);
private:
    bool m_IsRepeat;
};

class KeyReleasedEvent: public KeyEvent
{
public:
    KeyReleasedEvent(int keyCode, bool isRepeat = false) : KeyEvent(keyCode), m_IsRepeat(isRepeat) {}
    virtual ~KeyReleasedEvent() = default;
    EVENT_PROPERTIES(EventType::KeyReleased);
private:
    bool m_IsRepeat;
};


}

#endif
