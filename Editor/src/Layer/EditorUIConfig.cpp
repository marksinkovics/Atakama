#include "EditorUIConfig.hpp"

#include <format>

namespace Atakama::Editor
{

std::string WindowConfig::GetImGuiWindowId() const
{
    return fmt::format("{}###{}", Name, Id);
}

std::string WindowConfig::GetLayerName() const
{
    return fmt::format("{} Layer", Id);
}

}
