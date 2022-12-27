#ifndef WINDOW_EVENT_HPP
#define WINDOW_EVENT_HPP

#include "Event.hpp"

namespace OGLSample
{

class WindowResizeEvent: public Event
{
public:
    WindowResizeEvent(int width, int height): Event(EventType::WindowResize, "WindowResizeEvent"), m_Width(width), m_Height(height) {}
    virtual int GetWidth() const { return m_Width; }
    virtual int GetHeight() const { return m_Height; }
protected:
    int m_Width;
    int m_Height;
};

class WindowFrameBufferResizeEvent: public Event
{
public:
    WindowFrameBufferResizeEvent(int width, int height): Event(EventType::WindowFrameBufferResize, "WindowFrameBufferResizeEvent"), m_Width(width), m_Height(height) {}
    virtual int GetWidth() const { return m_Width; }
    virtual int GetHeight() const { return m_Height; }
protected:
    int m_Width;
    int m_Height;
};


class WindowCloseEvent: public Event
{
public:
    WindowCloseEvent(): Event(EventType::WindowClose, "WindowCloseEvent") {}
};

}

#endif
