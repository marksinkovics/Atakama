#include "VertexArray.hpp"
#include "OpenGL3/OpenGL3VertexArray.hpp"
#include "RenderTypes.hpp"

namespace OGLSample
{

Ref<VertexArray> VertexArray::Create()
{
    switch(g_RuntimeGlobalContext.m_GraphicsAPI)
    {
        case GraphicsAPI::None:
        {
            LOG_FATAL("GraphicsAPI::None is not supported!");
            break;
        }
        case GraphicsAPI::OpenGL3: return CreateRef<OpenGL3VertexArray>();
    }
}

}
