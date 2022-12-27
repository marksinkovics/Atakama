#include "Texture.hpp"
#include "OpenGL3/OpenGL3Texture.hpp"
#include "RenderTypes.hpp"


namespace OGLSample
{

Ref<Texture> Texture::Create(const std::filesystem::path& path)
{
    switch(g_RuntimeGlobalContext.m_GraphicsAPI)
    {
        case GraphicsAPI::None:
        {
            LOG_FATAL("GraphicsAPI::None is not supported!");
            break;
        }
        case GraphicsAPI::OpenGL3: return CreateRef<OpenGL3Texture>(path);
    }
}

Ref<Texture> Texture::Create(uint32_t id)
{
    switch(g_RuntimeGlobalContext.m_GraphicsAPI)
    {
        case GraphicsAPI::None:
        {
            LOG_FATAL("GraphicsAPI::None is not supported!");
            break;
        }
        case GraphicsAPI::OpenGL3: return CreateRef<OpenGL3Texture>(id);
    }
}

}
