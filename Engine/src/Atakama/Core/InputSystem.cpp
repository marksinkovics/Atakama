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
    dispatcher->subscribe<MouseScrolledEvent>(std::bind(&InputSystem::OnMouseScrollEvent, this, std::placeholders::_1));
}

void InputSystem::Update(float timestamp)
{
    m_DeltaCursorPos = { 0.f, 0.f };
    m_ScrollOffset = { 0.f, 0.f };
}

bool InputSystem::OnMouseMoved(MouseMovedEvent &event)
{
    m_DeltaCursorPos = m_LastCursorPos - event.GetPos();
    m_LastCursorPos = event.GetPos();
    
    return false;
}

bool InputSystem::OnMouseButtonPressed(MouseButtonPressedEvent &event)
{
    m_MouseButtonPressed.insert(event.GetButton());
    return false;
}

bool InputSystem::OnMouseButtonReleased(MouseButtonReleasedEvent &event)
{
    m_MouseButtonPressed.erase(event.GetButton());
    return false;
}

bool InputSystem::OnKeyPressed(KeyPressedEvent &event)
{
    m_KeyboardKeyPressed.insert(event.GetKeyCode());
    return false;
}

bool InputSystem::OnKeyReleased(KeyReleasedEvent &event)
{
    m_KeyboardKeyPressed.erase(event.GetKeyCode());
    return false;
}

bool InputSystem::OnMouseScrollEvent(MouseScrolledEvent& event)
{
    m_ScrollOffset += event.GetOffset();
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
    return m_KeyboardKeyPressed.find(key) != m_KeyboardKeyPressed.end();
}

bool InputSystem::IsShiftPressed() const
{
    return IsKeyPressed(GLFW_KEY_RIGHT_SHIFT) || IsKeyPressed(GLFW_KEY_LEFT_SHIFT);
}

glm::dvec2 InputSystem::GetMouseDelta()
{
    return m_DeltaCursorPos;
}

glm::dvec2 InputSystem::GetMouseScrollOffset()
{
    return m_ScrollOffset;
}

void InputSystem::Clear()
{
    ClearKeyboardEvents();
    ClearMouseEvents();
}

void InputSystem::ClearKeyboardEvents()
{
    m_KeyboardKeyPressed.clear();
}

void InputSystem::ClearMouseEvents()
{
    m_KeyboardKeyPressed.clear();
}

bool InputSystem::IsMouseButtonPressed(int button) const
{
    return m_MouseButtonPressed.find(button) != m_MouseButtonPressed.end();
}

}
