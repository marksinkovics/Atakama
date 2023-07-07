#ifndef ATAKAMA_INPUT_SYSTEM_HPP
#define ATAKAMA_INPUT_SYSTEM_HPP

namespace Atakama
{

class MouseMovedEvent;
class MouseButtonPressedEvent;
class MouseButtonReleasedEvent;
class KeyPressedEvent;
class KeyReleasedEvent;
class KeyEvent;
class MouseScrolledEvent;

class InputSystem
{
public:
    void Init();

    void Update(float timestamp);

    bool OnMouseMoved(MouseMovedEvent &event);
    bool OnMouseButtonPressed(MouseButtonPressedEvent &event);
    bool OnMouseButtonReleased(MouseButtonReleasedEvent &event);
    bool OnKeyPressed(KeyPressedEvent &event);
    bool OnKeyReleased(KeyReleasedEvent &event);
    bool OnMouseScrollEvent(MouseScrolledEvent& event);

    void SetFocusMode(bool mode);
    bool GetFocusMode() const;
    
    bool IsKeyPressed(uint32_t key) const;
    bool IsShiftPressed() const;
    bool IsMouseButtonPressed(int button) const;

    glm::dvec2 GetMouseDelta();
    glm::dvec2 GetMouseScrollOffset();
    
    void Clear();
    void ClearKeyboardEvents();
    void ClearMouseEvents();
private:
    glm::dvec2 m_LastCursorPos {0.f, 0.f};
    glm::dvec2 m_DeltaCursorPos {0.f, 0.f};
    glm::dvec2 m_ScrollOffset {0.f, 0.f};

    bool m_FocusMode {false};

    std::unordered_set<int> m_MouseButtonPressed;
    std::unordered_set<int> m_KeyboardKeyPressed;
};

}

#endif
