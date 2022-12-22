#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <chrono>

namespace OGLSample
{

class Engine
{
public:
    void Init();
    void Shutdown();
    void Run();
    void CalculateDeltaTime();
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_LastTime {std::chrono::high_resolution_clock::now()};
    float m_FrameTime;
};

}

#endif