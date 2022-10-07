#ifndef INPUT_HPP
#define INPUT_HPP

#include "Window.hpp"

namespace OGLSample
{

class Input
{
public:
    struct MousePos {
        double X;
        double Y;
    };

    static void EnableDragging(Ref<Window> window, bool enable);

    static bool IsKeyPressed(Ref<Window> window, uint32_t key);
    static Input::MousePos IsMouseMoved(Ref<Window> window, uint32_t button);

private:
    static inline bool MouseDraggingEnabled {false};
};

}

#endif
