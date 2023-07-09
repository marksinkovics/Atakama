#ifndef ATAKAMA_DROP_EVENT_HPP
#define ATAKAMA_DROP_EVENT_HPP

#include "Atakama/Events/Event.hpp"

#include <vector>
#include <filesystem>

namespace Atakama
{

    class DropEvent : public Event
    {
    public:
        DropEvent(std::vector<std::filesystem::path> paths) : m_Paths(paths) {}
        virtual ~DropEvent() = default;
        std::vector<std::filesystem::path> GetPaths() const { return m_Paths; }
        EVENT_PROPERTIES(EventType::Drop);
    protected:
        std::vector<std::filesystem::path> m_Paths;
    };

}

#endif
