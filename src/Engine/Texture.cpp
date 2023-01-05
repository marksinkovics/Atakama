#include "Texture.hpp"
#include "OpenGL3/OpenGL3Texture2D.hpp"
#include "RenderTypes.hpp"


namespace OGLSample
{

Ref<Texture> Texture2D::Create()
{
    switch(g_RuntimeGlobalContext.m_GraphicsAPI)
    {
        case GraphicsAPI::None:
        {
            LOG_FATAL("GraphicsAPI::None is not supported!");
            break;
        }
        case GraphicsAPI::OpenGL3: return CreateRef<OpenGL3Texture2D>();
    }
}

Ref<Texture> Texture2D::Create(const std::filesystem::path& path)
{
    switch(g_RuntimeGlobalContext.m_GraphicsAPI)
    {
        case GraphicsAPI::None:
        {
            LOG_FATAL("GraphicsAPI::None is not supported!");
            break;
        }
        case GraphicsAPI::OpenGL3: return CreateRef<OpenGL3Texture2D>(path);
    }
}

Ref<Texture> Texture2D::Create(uint32_t id)
{
    switch(g_RuntimeGlobalContext.m_GraphicsAPI)
    {
        case GraphicsAPI::None:
        {
            LOG_FATAL("GraphicsAPI::None is not supported!");
            break;
        }
        case GraphicsAPI::OpenGL3: return CreateRef<OpenGL3Texture2D>(id);
    }
}

}
