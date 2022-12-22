#include "Engine.hpp"

#include "Window.hpp"

namespace OGLSample
{

void Engine::Init()
{

}

void Engine::Shutdown()
{

}

void Engine::Run()
{
    CalculateDeltaTime();
    g_RuntimeGlobalContext.m_Window->SwapBuffers();
    g_RuntimeGlobalContext.m_Window->PollEvents();




}

void Engine::CalculateDeltaTime()
{
    auto timePoint = std::chrono::high_resolution_clock::now();
    m_FrameTime = std::chrono::duration<float, std::chrono::seconds::period>(timePoint - m_LastTime).count();
    m_LastTime = timePoint;
}

}