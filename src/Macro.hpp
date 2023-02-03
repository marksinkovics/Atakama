#ifndef ATAKAMA_MACRO_HPP
#define ATAKAMA_MACRO_HPP

#ifdef NDEBUG
#define ASSERT(statement)
#else
#define ASSERT(statement) assert(statement)
#endif


#define LOG_HELPER(LOG_LEVEL, ...) \
    g_RuntimeGlobalContext.m_LogSystem->log(LOG_LEVEL, __VA_ARGS__);

#define LOG_TRACE(...) LOG_HELPER(Atakama::LogSystem::Level::Trace, __VA_ARGS__);
#define LOG_DEBUG(...) LOG_HELPER(Atakama::LogSystem::Level::Debug, __VA_ARGS__);
#define LOG_INFO(...)  LOG_HELPER(Atakama::LogSystem::Level::Info,  __VA_ARGS__);
#define LOG_WARN(...)  LOG_HELPER(Atakama::LogSystem::Level::Warn,  __VA_ARGS__);
#define LOG_ERROR(...) LOG_HELPER(Atakama::LogSystem::Level::Error, __VA_ARGS__);
#define LOG_FATAL(...) LOG_HELPER(Atakama::LogSystem::Level::Fatal, __VA_ARGS__);

#endif
