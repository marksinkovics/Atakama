#include "GraphicsContext.hpp"
#include "OpenGL3/OpenGL3GraphicsContext.hpp"

namespace Atakama
{

Ref<GraphicsContext> GraphicsContext::Create()
{
    switch(g_RuntimeGlobalContext.m_GraphicsAPI)
    {
        case GraphicsAPI::None:
        {
            LOG_FATAL("GraphicsAPI::None is not supported!");
            break;
        }
        case GraphicsAPI::OpenGL3: return CreateRef<OpenGL3GraphicsContext>();
    }
}

}
