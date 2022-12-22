#ifndef INPUT_HPP
#define INPUT_HPP

#include "Window.hpp"

#include <map>

namespace OGLSample
{

class MouseMovedEvent;
class MouseButtonPressedEvent;
class MouseButtonReleasedEvent;
class KeyPressedEvent;
class KeyReleasedEvent;

class Input
{
public:
    void Init();

    bool OnMouseMoved(MouseMovedEvent &event);
    bool OnMouseButtonPressed(MouseButtonPressedEvent &event);
    bool OnMouseButtonReleased(MouseButtonReleasedEvent &event);
    bool OnKeyPressed(KeyPressedEvent &event);
    bool OnKeyReleased(KeyReleasedEvent &event);

    void SetFocusMode(bool mode);
    bool GetFocusMode() const;
    
    bool IsKeyPressed(uint32_t key) const;
    bool IsMouseButtonPressed(int button) const;

    glm::dvec2 GetMouseDelta();
    
    void Clear();
private:
    glm::dvec2 m_LastCursorPos;
    glm::dvec2 m_DeltaCursorPos;
    bool m_FocusMode {false};
    
    std::map<int, bool> m_ButtonPressed;
    std::map<int, bool> m_KeyPressed;
};

}

#endif
