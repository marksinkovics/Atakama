#ifndef ATAKAMA_MESH_OBJECT_HPP
#define ATAKAMA_MESH_OBJECT_HPP

#include "Atakama/Engine/RenderTypes.hpp"
#include "Atakama/Engine/Texture.hpp"

#include "Atakama/Engine/Vertex.hpp"
#include "Atakama/Engine/VertexBuffer.hpp"
#include "Atakama/Engine/IndexBuffer.hpp"
#include "Atakama/Engine/VertexArray.hpp"

#include "Atakama/Scene/Components/TransformComponent.hpp"

namespace Atakama
{

class MeshObject
{
public:
    MeshObject(std::vector<Vertex>& vertices);
    MeshObject(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

    ~MeshObject();

    DrawingMode GetMode();
    void SetMode(DrawingMode mode);
    
    Ref<VertexArray>& GetVertexArray();
private:
    DrawingMode m_Mode = DrawingMode::Triangles;

    Ref<VertexBuffer> m_VertexBuffer;
    Ref<IndexBuffer> m_IndexBuffer;
    Ref<VertexArray> m_VertexArray;
};

}

#endif
