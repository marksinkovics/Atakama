#ifndef POINT_LIGHT_HPP
#define POINT_LIGHT_HPP

namespace OGLSample
{

class Mesh;

class PointLight
{
public:
    PointLight(const glm::vec4& position, const glm::vec4& color);
    virtual ~PointLight() = default;
    virtual glm::vec4& GetPositionRef();
    virtual glm::vec4& GetColorRef();
    virtual glm::vec4 GetPosition() const;
    virtual glm::vec4 GetColor() const;
    virtual Ref<Mesh> GetMesh() const;
protected:
    glm::vec4 m_Position;
    glm::vec4 m_Color;
    Ref<Mesh> m_Mesh;
};

}

#endif
