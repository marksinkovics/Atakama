#ifndef ATAKAMA_EDITOR_APPLICATION_HPP
#define ATAKAMA_EDITOR_APPLICATION_HPP

#include <Atakama/Core/Application.hpp>

namespace Atakama
{

class DropEvent;

namespace Editor
{

class EditorLayer;

class EditorApplication : public Application
{
public:
    EditorApplication();
    virtual bool OnDrop(DropEvent& event);
private:
    std::map<WindowId, WindowConfig>& m_WindowConfigs;
};

}

}

#endif
