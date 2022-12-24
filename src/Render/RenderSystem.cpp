#include "RenderSystem.hpp"
#include "Render/VertexBuffer.hpp"

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

void RenderSystem::Init()
{
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);
    glEnable(GL_LINE_SMOOTH);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void RenderSystem::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderSystem::SetClearColor(const glm::vec4& clearColor)
{
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
}

void RenderSystem::Draw(DrawingMode mode, Ref<VertexArray>& vertexArray) const
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

}
