#include "RenderSystem.hpp"
#include "Engine/VertexBuffer.hpp"

#include "OpenGL3/OpenGL3RenderSystem.hpp"

namespace OGLSample
{

Ref<RenderSystem> RenderSystem::Create()
{
    switch(g_RuntimeGlobalContext.m_GraphicsAPI)
    {
        case GraphicsAPI::None:
        {
            LOG_FATAL("GraphicsAPI::None is not supported!");
            break;
        }
        case GraphicsAPI::OpenGL3: return CreateRef<OpenGL3RenderSystem>();
    }
}

}

