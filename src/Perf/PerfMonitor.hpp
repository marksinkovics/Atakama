#ifndef PERF_MONITOR_HPP
#define PERF_MONITOR_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace OGLSample
{

class PerfMonitor
{
public:
    PerfMonitor();
    ~PerfMonitor() = default;

    void StartCPUTimer();
    void StopCPUTimer();

    void StartGPUTimer();
    void StopGPUTimer();

    // Return in millisec
    float GetCPUTime();

    // Return in millisec
    float GetGPUTime();
    bool GetGPUAvailable();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_CPUStartTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_CPUStopTime;
    float m_CPUTime;

    GLuint m_TimeQuery;
    bool m_GPUTimerActivated;
    uint32_t m_GPUTime;
    int32_t m_GPUTimerAvailable;
};

}


#endif