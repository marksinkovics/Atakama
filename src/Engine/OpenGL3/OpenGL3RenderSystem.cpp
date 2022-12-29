#include "Engine/OpenGL3/OpenGL3RenderSystem.hpp"
#include "Engine/VertexArray.hpp"

namespace OGLSample
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
        glDrawElements(GetOpenGLDrawingMode(mode), vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
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

void OpenGL3RenderSystem::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    glViewport(x, y, width, height);
}

}

