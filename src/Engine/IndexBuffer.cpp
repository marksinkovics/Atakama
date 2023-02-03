#include "IndexBuffer.hpp"
#include "OpenGL3/OpenGL3IndexBuffer.hpp"
#include "RenderTypes.hpp"

namespace Atakama
{

Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, size_t count)
{
    switch(g_RuntimeGlobalContext.m_GraphicsAPI)
    {
        case GraphicsAPI::None:
        {
            LOG_FATAL("GraphicsAPI::None is not supported!");
            break;
        }
        case GraphicsAPI::OpenGL3: return CreateRef<OpenGL3IndexBuffer>(indices, count);
    }
}

}
