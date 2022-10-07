#include "Input.hpp"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace OGLSample
{

static Input::MousePos OriginalMousePos;

void Input::EnableDragging(const Ref<Window> window, bool enable)
{
    if (enable)
    {
        glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else
    {
        glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    Input::MouseDraggingEnabled = enable;
    glfwSetCursorPos(window->GetWindow(), window->GetWidth()/2, window->GetHeight()/2);
}

bool Input::IsKeyPressed(const Ref<Window> window, uint32_t key)
{
    return (glfwGetKey(window->GetWindow(), key) == GLFW_PRESS);
}

Input::MousePos Input::IsMouseMoved(Ref<Window> window, uint32_t button)
{
    if (MouseDraggingEnabled)
    {
        Input::MousePos pos {0, 0};
        Input::MousePos delta {0, 0};

        if (glfwGetMouseButton(window->GetWindow(), button) == GLFW_PRESS) {
            glfwGetCursorPos(window->GetWindow(), &pos.X, &pos.Y);
            delta.X = pos.X - OriginalMousePos.X;
            delta.Y = pos.Y - OriginalMousePos.Y;
        }
        glfwGetCursorPos(window->GetWindow(), &OriginalMousePos.X, &OriginalMousePos.Y);
        return {-delta.X, -delta.Y};
    } else {
        Input::MousePos pos;
        glfwGetCursorPos(window->GetWindow(), &pos.X, &pos.Y);
        glfwSetCursorPos(window->GetWindow(), window->GetWidth()/2, window->GetHeight()/2);
        return {window->GetWidth()/2  - pos.X, window->GetHeight()/2 - pos.Y};
    }
}

}
