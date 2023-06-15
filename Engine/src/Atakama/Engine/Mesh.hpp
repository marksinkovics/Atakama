#ifndef ATAKAMA_MESH_HPP
#define ATAKAMA_MESH_HPP

#include "Atakama/Engine/RenderTypes.hpp"
#include "Atakama/Engine/Texture.hpp"

#include "Atakama/Engine/Vertex.hpp"
#include "Atakama/Engine/VertexBuffer.hpp"
#include "Atakama/Engine/IndexBuffer.hpp"
#include "Atakama/Engine/VertexArray.hpp"

#include "Atakama/Scene/Components/TransformComponent.hpp"

namespace Atakama
{

class Mesh
{
public:
    Mesh(std::vector<Vertex>& vertices);
    Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

    ~Mesh();

    DrawingMode GetMode();
    void SetMode(DrawingMode mode);

    std::string GetTextureId();
    void SetTextureId(const std::string& textureId);
    bool HasTextureId();

    Ref<VertexArray>& GetVertexArray();
private:
    DrawingMode m_Mode = DrawingMode::Triangles;
    std::string m_TextureId = "";

    Ref<VertexBuffer> m_VertexBuffer;
    Ref<IndexBuffer> m_IndexBuffer;
    Ref<VertexArray> m_VertexArray;
};

}

#endif
