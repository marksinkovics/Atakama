#include "Atakama/Engine/OpenGL3/OpenGL3RenderSystem.hpp"
#include "Atakama/Engine/VertexArray.hpp"

#include <GL/glew.h>

namespace Atakama
{

GLuint GetOpenGLDrawingMode(DrawingMode mode)
{
    switch (mode)
    {
        case DrawingMode::Triangles: return GL_TRIANGLES;
        case DrawingMode::Lines: return GL_LINES;
    };
}

void OpenGL3RenderSystem::Init()
{
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_CUBE_MAP);
}

void OpenGL3RenderSystem::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGL3RenderSystem::SetClearColor(const glm::vec4& clearColor)
{
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
}

void OpenGL3RenderSystem::Draw(DrawingMode mode, Ref<VertexArray>& vertexArray)
{
    vertexArray->Bind();
    
    if (vertexArray->GetIndexBuffer() && vertexArray->GetIndexBuffer()->GetCount() > 0)
    {
        glDrawElements(GetOpenGLDrawingMode(mode), (GLsizei)vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
    else
    {
        glDrawArrays(GetOpenGLDrawingMode(mode), 0, vertexArray->GetVertexCount());
    }
    
    vertexArray->Unbind();
}

void OpenGL3RenderSystem::SetDepthTest(bool value)
{
    if (value)
    {
        glEnable(GL_DEPTH_TEST);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }
}

GLenum GetOpenGLBaseType(DepthCompare depthCompare)
{
    switch (depthCompare)
    {
        case DepthCompare::Never: return GL_NEVER;
        case DepthCompare::Less: return GL_LESS;
        case DepthCompare::Equal: return GL_EQUAL;
        case DepthCompare::LessOrEqual: return GL_LEQUAL;
        case DepthCompare::Greater: return GL_GREATER;
        case DepthCompare::NotEqual: return GL_NOTEQUAL;
        case DepthCompare::GreaterOrEqual: return GL_GEQUAL;
        case DepthCompare::Always: return GL_ALWAYS;
    }
}

void OpenGL3RenderSystem::SetDepthCompare(DepthCompare depthCompare)
{
    GLenum value = GetOpenGLBaseType(depthCompare);
    glDepthFunc(value);
}

void OpenGL3RenderSystem::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    glViewport(x, y, width, height);
}

}

