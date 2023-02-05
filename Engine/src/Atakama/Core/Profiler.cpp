#include "Profiler.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Atakama/Engine/RenderTypes.hpp"

namespace Atakama
{

Profiler::Profiler()
 : m_GPUTimerActivated(false), m_CPUTime(0.0f), m_GPUTime(0)
{
    if (g_RuntimeGlobalContext.m_GraphicsAPI != GraphicsAPI::OpenGL3)
        return;

    glGenQueries(1, &m_TimeQuery);
}

void Profiler::Start()
{
    StartCPUTimer();
    StartGPUTimer();
}

void Profiler::Stop()
{
    StopGPUTimer();
    StopCPUTimer();
}

void Profiler::StartCPUTimer()
{
    m_CPUStartTime = std::chrono::high_resolution_clock::now();
}

void Profiler::StopCPUTimer()
{
    m_CPUStopTime = std::chrono::high_resolution_clock::now();
    m_CPUTime = std::chrono::duration<float, std::chrono::milliseconds::period>(m_CPUStopTime - m_CPUStartTime).count();
}

void Profiler::StartGPUTimer()
{
    if (g_RuntimeGlobalContext.m_GraphicsAPI != GraphicsAPI::OpenGL3)
        return;
    
    glGetQueryObjectiv(m_TimeQuery, GL_QUERY_RESULT_AVAILABLE, &m_GPUTimerAvailable);

    if(m_GPUTimerAvailable)
    {
        glGetQueryObjectuiv(m_TimeQuery, GL_QUERY_RESULT, &m_GPUTime);
        glBeginQuery(GL_TIME_ELAPSED, m_TimeQuery);
    } else if (!m_GPUTimerActivated)
    {
        glBeginQuery(GL_TIME_ELAPSED, m_TimeQuery);
    }
}

void Profiler::StopGPUTimer()
{
    if (g_RuntimeGlobalContext.m_GraphicsAPI != GraphicsAPI::OpenGL3)
        return;

    if(m_GPUTimerAvailable)
    {
        glEndQuery(GL_TIME_ELAPSED);
    }
    else if (!m_GPUTimerActivated)
    {
        glEndQuery(GL_TIME_ELAPSED);
        m_GPUTimerActivated = true;
    }
}

float Profiler::GetCPUTime()
{
    return m_CPUTime;
}

float Profiler::GetGPUTime()
{
    return m_GPUTime / 1000000.f;
}

bool Profiler::GetGPUAvailable()
{
    return m_GPUTimerAvailable;
}

}
