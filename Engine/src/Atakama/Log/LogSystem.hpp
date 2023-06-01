#ifndef ATAKAMA_LOG_SYSTEM_HPP
#define ATAKAMA_LOG_SYSTEM_HPP

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Atakama
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
    void log(Level level, fmt::format_string<ARGS...> format_str, ARGS&&... args)
    {
        switch(level)
        {
            case Level::Trace:
                m_Logger->trace(format_str, std::forward<ARGS>(args)...);
                break;
            case Level::Debug:
                m_Logger->debug(format_str, std::forward<ARGS>(args)...);
                break;
            case Level::Info:
                m_Logger->info(format_str, std::forward<ARGS>(args)...);
                break;
            case Level::Warn:
                m_Logger->warn(format_str, std::forward<ARGS>(args)...);
                break;
            case Level::Error:
                m_Logger->error(format_str, std::forward<ARGS>(args)...);
                break;
            case Level::Fatal:
                m_Logger->critical(format_str, std::forward<ARGS>(args)...);
                fatalCallback(format_str, std::forward<ARGS>(args)...);
                break;
            default:
                break;
        }
    }
    
    template<typename... ARGS>
    void fatalCallback(fmt::format_string<ARGS...> format_str, ARGS&&... args)
    {
        const std::string str = fmt::format(format_str, std::forward<ARGS>(args)...);
        throw std::runtime_error(str);
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
