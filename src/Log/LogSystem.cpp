#include "LogSystem.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/async.h>


namespace OGLSample
{

LogSystem::LogSystem()
{
    std::vector<spdlog::sink_ptr> sinks;
    sinks.emplace_back(CreateRef<spdlog::sinks::stdout_sink_mt>());
    sinks.emplace_back(CreateRef<spdlog::sinks::basic_file_sink_mt>("OGLSample.log", true));
    
    sinks[0]->set_pattern("[%T][%-5l]: %v");
    sinks[1]->set_pattern("%+");

    spdlog::init_thread_pool(8192, 1);

    m_Logger = CreateRef<spdlog::async_logger>("OGLSample", begin(sinks), end(sinks), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    spdlog::register_logger(m_Logger);
    m_Logger->set_level(spdlog::level::trace);
    m_Logger->flush_on(spdlog::level::trace);
}

LogSystem::~LogSystem()
{
    m_Logger->flush();
    spdlog::drop_all();
}

}
