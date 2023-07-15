#include "EditorUIConfig.hpp"

#include <format>

namespace Atakama::Editor
{

std::string WindowConfig::GetImGuiWindowId() const
{
    return std::format("{}###{}", Name, Id);
}

std::string WindowConfig::GetLayerName() const
{
    return std::format("{} Layer", Id);
}

}
