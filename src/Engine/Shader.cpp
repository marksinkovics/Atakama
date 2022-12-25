#include "Shader.hpp"
#include "RenderTypes.hpp"
#include "Engine/OpenGL3/OpenGL3Shader.hpp"

namespace OGLSample
{

Ref<Shader> Shader::Create(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
{
    switch(g_RuntimeGlobalContext.m_GraphicsAPI)
    {
        case GraphicsAPI::None:
        {
            LOG_FATAL("GraphicsAPI::None is not supported!");
            break;
        }
        case GraphicsAPI::OpenGL3: return CreateRef<OpenGL3Shader>(vertexPath, fragmentPath);
    }
}

}
