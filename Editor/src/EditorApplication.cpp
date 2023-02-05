#include "EditorApplication.hpp"

#include "Layer/StatsLayer.hpp"
#include "Layer/ViewportLayer.hpp"
#include "Layer/DepthViewLayer.hpp"
#include "Layer/SceneLayer.hpp"


namespace Atakama::Editor
{

EditorApplication::EditorApplication()
: Application()
{
    AddLayer(new StatsLayer());
    AddLayer(new ViewportLayer());
    AddLayer(new DepthViewLayer());
    AddLayer(new SceneLayer());
}

}
