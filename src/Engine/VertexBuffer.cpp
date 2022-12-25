#include "VertexBuffer.hpp"
#include "OpenGL3/OpenGL3VertexBuffer.hpp"
#include "RenderTypes.hpp"

namespace OGLSample
{

Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
{
    switch(g_RuntimeGlobalContext.m_GraphicsAPI)
    {
        case GraphicsAPI::None:
        {
            LOG_FATAL("GraphicsAPI::None is not supported!");
            break;
        }
        case GraphicsAPI::OpenGL3: return CreateRef<OpenGL3VertexBuffer>(size);
    }
}

Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
{
    switch(g_RuntimeGlobalContext.m_GraphicsAPI)
    {
        case GraphicsAPI::None:
        {
            LOG_FATAL("GraphicsAPI::None is not supported!");
            break;
        }
        case GraphicsAPI::OpenGL3: return CreateRef<OpenGL3VertexBuffer>(vertices, size);
    }
}

}
