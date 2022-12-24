#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

namespace OGLSample
{

class VertexArray;

enum class DrawingMode {
    Triangles, Lines
};

class RenderSystem
{
public:
    void Init();
    void Clear() const;
    void SetClearColor(const glm::vec4& clearColor);
    void Draw(DrawingMode mode, Ref<VertexArray>& vertexArray) const;
private:
    glm::vec4 m_ClearColor;
};

}

#endif
