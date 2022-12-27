#include "FrameBuffer.hpp"
#include "OpenGL3/OpenGL3FrameBuffer.hpp"
#include "RenderTypes.hpp"

namespace OGLSample
{

Ref<FrameBuffer> FrameBuffer::Create()
{
    switch(g_RuntimeGlobalContext.m_GraphicsAPI)
    {
        case GraphicsAPI::None:
        {
            LOG_FATAL("GraphicsAPI::None is not supported!");
            break;
        }
        case GraphicsAPI::OpenGL3: return CreateRef<OpenGL3FrameBuffer>();
    }
}

}
