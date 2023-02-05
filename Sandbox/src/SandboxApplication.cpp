#include "SandboxApplication.hpp"

#include "Layer/StatsLayer.hpp"


namespace Atakama::Sandbox
{

SandboxApplication::SandboxApplication()
: Application()
{
    AddLayer(new StatsLayer());
}

}
