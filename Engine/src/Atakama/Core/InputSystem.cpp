#include "Atakama/Core/InputSystem.hpp"
#include "Atakama/Events/EventDispatcher.hpp"
#include "Atakama/Events/MouseEvent.hpp"
#include "Atakama/Events/KeyEvent.hpp"
#include "Atakama/Core/Window.hpp"

#include <GLFW/glfw3.h>

#include <iostream>

namespace Atakama
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
    m_ButtonPressed.insert(event.GetButton());
    return false;
}

bool InputSystem::OnMouseButtonReleased(MouseButtonReleasedEvent &event)
{
    m_ButtonPressed.erase(event.GetButton());
    return false;
}

bool InputSystem::OnKeyPressed(KeyPressedEvent &event)
{
    m_KeyPressed.insert(event.GetKeyCode());
    return false;
}

bool InputSystem::OnKeyReleased(KeyReleasedEvent &event)
{
    m_KeyPressed.erase(event.GetKeyCode());
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
    return m_KeyPressed.find(key) != m_KeyPressed.end();
}

glm::dvec2 InputSystem::GetMouseDelta()
{
    return m_DeltaCursorPos;
}

void InputSystem::Clear()
{
    m_DeltaCursorPos = {0.f, 0.f};
}

void InputSystem::ClearKeyboardEvents()
{
    m_KeyPressed.clear();
}

bool InputSystem::IsMouseButtonPressed(int button) const
{
    return m_ButtonPressed.find(button) != m_ButtonPressed.end();
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

    return Movement::None;

}

}
