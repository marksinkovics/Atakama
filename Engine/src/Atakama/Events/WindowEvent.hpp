#ifndef ATAKAMA_WINDOW_EVENT_HPP
#define ATAKAMA_WINDOW_EVENT_HPP

#include "Event.hpp"

namespace Atakama
{

class WindowResizeEvent: public Event
{
public:
    WindowResizeEvent(int width, int height): m_Width(width), m_Height(height) {}
    virtual ~WindowResizeEvent() = default;
    virtual int GetWidth() const { return m_Width; }
    virtual int GetHeight() const { return m_Height; }
    EVENT_PROPERTIES(EventType::WindowResize);
protected:
    int m_Width;
    int m_Height;
};

class WindowFrameBufferResizeEvent: public Event
{
public:
    WindowFrameBufferResizeEvent(int width, int height): m_Width(width), m_Height(height) {}
    virtual ~WindowFrameBufferResizeEvent() = default;
    virtual int GetWidth() const { return m_Width; }
    virtual int GetHeight() const { return m_Height; }
    EVENT_PROPERTIES(EventType::WindowFrameBufferResize);
protected:
    int m_Width;
    int m_Height;
};


class WindowCloseEvent: public Event
{
public:
    WindowCloseEvent() {}
    virtual ~WindowCloseEvent() = default;
    EVENT_PROPERTIES(EventType::WindowClose);
};

}

#endif
