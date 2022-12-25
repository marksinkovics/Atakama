#ifndef LOG_SYSTEM_HPP
#define LOG_SYSTEM_HPP

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace OGLSample
{

class LogSystem final
{
public:
    enum class Level {
        Trace, Debug, Info, Warn, Error, Fatal
    };
public:
    LogSystem();
    ~LogSystem();
    
    template<typename... ARGS>
    void log(Level level, ARGS&&... args)
    {
        switch(level)
        {
            case Level::Trace:
                m_Logger->trace(std::forward<ARGS>(args)...);
                break;
            case Level::Debug:
                m_Logger->debug(std::forward<ARGS>(args)...);
                break;
            case Level::Info:
                m_Logger->info(std::forward<ARGS>(args)...);
                break;
            case Level::Warn:
                m_Logger->warn(std::forward<ARGS>(args)...);
                break;
            case Level::Error:
                m_Logger->error(std::forward<ARGS>(args)...);
                break;
            case Level::Fatal:
                m_Logger->critical(std::forward<ARGS>(args)...);
                fatalCallback(std::forward<ARGS>(args)...);
                break;
            default:
                break;
        }
    }
    
    template<typename... ARGS>
    void fatalCallback(ARGS&&... args)
    {
        const std::string format_str = fmt::format(std::forward<ARGS>(args)...);
        throw std::runtime_error(format_str);
    }
private:
    Ref<spdlog::logger> m_Logger;
};

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
    return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
    return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
    return os << glm::to_string(quaternion);
}

}

#endif
