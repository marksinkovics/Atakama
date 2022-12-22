#include "Input.hpp"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Events/EventDispatcher.hpp"
#include "Events/MouseEvent.hpp"
#include "Events/KeyEvent.hpp"

namespace OGLSample
{

void Input::Init()
{
    Ref<EventDispatcher> dispatcher = g_RuntimeGlobalContext.m_Dispatcher;
    dispatcher->subscribe<MouseMovedEvent>(EventType::MouseMoved, std::bind(&Input::OnMouseMoved, this, std::placeholders::_1));
    dispatcher->subscribe<MouseButtonPressedEvent>(EventType::MouseButtonPressed, std::bind(&Input::OnMouseButtonPressed, this, std::placeholders::_1));
    dispatcher->subscribe<MouseButtonReleasedEvent>(EventType::MouseButtonReleased, std::bind(&Input::OnMouseButtonReleased, this, std::placeholders::_1));
    dispatcher->subscribe<KeyPressedEvent>(EventType::KeyPressed, std::bind(&Input::OnKeyPressed, this, std::placeholders::_1));
    dispatcher->subscribe<KeyReleasedEvent>(EventType::KeyReleased, std::bind(&Input::OnKeyReleased, this, std::placeholders::_1));
}

bool Input::OnMouseMoved(MouseMovedEvent &event)
{
    m_DeltaCursorPos = m_LastCursorPos - event.GetPos();
    m_LastCursorPos = event.GetPos();
    
    return false;
}

bool Input::OnMouseButtonPressed(MouseButtonPressedEvent &event)
{
    auto it = m_ButtonPressed.find(event.GetButton());
    if (it == m_ButtonPressed.end())
        m_ButtonPressed[event.GetButton()] = true;
    
    return false;
}

bool Input::OnMouseButtonReleased(MouseButtonReleasedEvent &event)
{
    auto it = m_ButtonPressed.find(event.GetButton());
    if (it != m_ButtonPressed.end())
        m_ButtonPressed.erase(it);
    
    return false;
}

bool Input::OnKeyPressed(KeyPressedEvent &event)
{
    auto it = m_KeyPressed.find(event.GetKeyCode());
    if (it == m_KeyPressed.end())
        m_KeyPressed[event.GetKeyCode()] = true;
    
    return false;
}

bool Input::OnKeyReleased(KeyReleasedEvent &event)
{
    auto it = m_KeyPressed.find(event.GetKeyCode());
    if (it != m_KeyPressed.end())
        m_KeyPressed.erase(it);
    
    return false;
}

void Input::SetFocusMode(bool mode)
{
    m_FocusMode = mode;
    glfwSetInputMode(g_RuntimeGlobalContext.m_Window->GetWindow(), GLFW_CURSOR, mode ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

bool Input::GetFocusMode() const
{
    return m_FocusMode;
}

bool Input::IsKeyPressed(uint32_t key) const
{
    auto it = m_KeyPressed.find(key);
    if (it == m_KeyPressed.end())
        return false;
    return it->second;
}

glm::dvec2 Input::GetMouseDelta()
{
    return m_DeltaCursorPos;
}

void Input::Clear()
{
    m_DeltaCursorPos = {0.f, 0.f};
}

bool Input::IsMouseButtonPressed(int button) const
{
    auto it = m_ButtonPressed.find(button);
    if (it == m_ButtonPressed.end())
        return false;
    return it->second;
}

}
