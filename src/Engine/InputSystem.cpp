#include "InputSystem.hpp"
#include "Events/EventDispatcher.hpp"
#include "Events/MouseEvent.hpp"
#include "Events/KeyEvent.hpp"

#include <GLFW/glfw3.h>

#include <iostream>

namespace OGLSample
{

void InputSystem::Init()
{
    Ref<EventDispatcher> dispatcher = g_RuntimeGlobalContext.m_Dispatcher;
    dispatcher->subscribe<MouseMovedEvent>(std::bind(&InputSystem::OnMouseMoved, this, std::placeholders::_1));
    dispatcher->subscribe<MouseButtonPressedEvent>(std::bind(&InputSystem::OnMouseButtonPressed, this, std::placeholders::_1));
    dispatcher->subscribe<MouseButtonReleasedEvent>(std::bind(&InputSystem::OnMouseButtonReleased, this, std::placeholders::_1));
    dispatcher->subscribe<KeyPressedEvent>(std::bind(&InputSystem::OnKeyPressed, this, std::placeholders::_1));
    dispatcher->subscribe<KeyReleasedEvent>(std::bind(&InputSystem::OnKeyReleased, this, std::placeholders::_1));
}

bool InputSystem::OnMouseMoved(MouseMovedEvent &event)
{
    m_DeltaCursorPos = m_LastCursorPos - event.GetPos();
    m_LastCursorPos = event.GetPos();
    
    return false;
}

bool InputSystem::OnMouseButtonPressed(MouseButtonPressedEvent &event)
{
    auto it = m_ButtonPressed.find(event.GetButton());
    if (it == m_ButtonPressed.end())
        m_ButtonPressed[event.GetButton()] = true;
    
    return false;
}

bool InputSystem::OnMouseButtonReleased(MouseButtonReleasedEvent &event)
{
    auto it = m_ButtonPressed.find(event.GetButton());
    if (it != m_ButtonPressed.end())
        m_ButtonPressed.erase(it);
    
    return false;
}

bool InputSystem::OnKeyPressed(KeyPressedEvent &event)
{
    auto it = m_KeyPressed.find(event.GetKeyCode());
    if (it == m_KeyPressed.end())
        m_KeyPressed[event.GetKeyCode()] = true;
    
    return false;
}

bool InputSystem::OnKeyReleased(KeyReleasedEvent &event)
{
    auto it = m_KeyPressed.find(event.GetKeyCode());
    if (it != m_KeyPressed.end())
        m_KeyPressed.erase(it);
    
    return false;
}

void InputSystem::SetFocusMode(bool mode)
{
    m_FocusMode = mode;
    glfwSetInputMode(g_RuntimeGlobalContext.m_Window->GetWindow(), GLFW_CURSOR, mode ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

bool InputSystem::GetFocusMode() const
{
    return m_FocusMode;
}

bool InputSystem::IsKeyPressed(uint32_t key) const
{
    auto it = m_KeyPressed.find(key);
    if (it == m_KeyPressed.end())
        return false;
    return it->second;
}

glm::dvec2 InputSystem::GetMouseDelta()
{
    return m_DeltaCursorPos;
}

void InputSystem::Clear()
{
    m_DeltaCursorPos = {0.f, 0.f};
}

bool InputSystem::IsMouseButtonPressed(int button) const
{
    auto it = m_ButtonPressed.find(button);
    if (it == m_ButtonPressed.end())
        return false;
    return it->second;
}

bool InputSystem::IsMovement(Movement movement) const
{
    if (movement == Movement::Forward)
    {
        return IsKeyPressed(GLFW_KEY_UP) || IsKeyPressed(GLFW_KEY_W);
    }
    
    if (movement == Movement::Backward)
    {
        return IsKeyPressed(GLFW_KEY_DOWN) || IsKeyPressed(GLFW_KEY_S);
    }

    if (movement == Movement::Left)
    {
        return IsKeyPressed(GLFW_KEY_LEFT) || IsKeyPressed(GLFW_KEY_A);
    }
    
    if (movement == Movement::Right)
    {
        return IsKeyPressed(GLFW_KEY_RIGHT) || IsKeyPressed(GLFW_KEY_D);
    }
    
    if (movement == Movement::Up)
    {
        return IsKeyPressed(GLFW_KEY_Q);
    }
    
    if (movement == Movement::Down)
    {
        return IsKeyPressed(GLFW_KEY_E);
    }

}

Movement InputSystem::GetMovement() const
{
    if (IsKeyPressed(GLFW_KEY_UP) || IsKeyPressed(GLFW_KEY_W))
    {
        return Movement::Forward;
    }

    if (IsKeyPressed(GLFW_KEY_DOWN) || IsKeyPressed(GLFW_KEY_S))
    {
        return Movement::Backward;
    }

    if (IsKeyPressed(GLFW_KEY_RIGHT) || IsKeyPressed(GLFW_KEY_D))
    {
        return Movement::Right;
    }

    if (IsKeyPressed(GLFW_KEY_LEFT) || IsKeyPressed(GLFW_KEY_A))
    {
        return Movement::Left;
    }
    
    if (IsKeyPressed(GLFW_KEY_Q))
    {
        return Movement::Up;
    }

    if (IsKeyPressed(GLFW_KEY_E))
    {
        return Movement::Down;
    }


}

}
