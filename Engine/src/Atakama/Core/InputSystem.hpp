#ifndef ATAKAMA_INPUT_SYSTEM_HPP
#define ATAKAMA_INPUT_SYSTEM_HPP

namespace Atakama
{

class MouseMovedEvent;
class MouseButtonPressedEvent;
class MouseButtonReleasedEvent;
class KeyPressedEvent;
class KeyReleasedEvent;

enum class Movement
{
    None,
    Forward, Backward,
    Left, Right,
    Up, Down
};

class InputSystem
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
    bool IsMovement(Movement movement) const;
    Movement GetMovement() const;

    glm::dvec2 GetMouseDelta();
    
    void Clear();
private:
    glm::dvec2 m_LastCursorPos {0.f, 0.f};
    glm::dvec2 m_DeltaCursorPos {0.f, 0.f};
    bool m_FocusMode {false};

    std::unordered_set<int> m_ButtonPressed;
    std::unordered_set<int> m_KeyPressed;
};

}

#endif
