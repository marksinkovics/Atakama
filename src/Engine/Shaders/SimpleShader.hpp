#ifndef FLAT_COLOR_SHADER
#define FLAT_COLOR_SHADER

#include "Engine/Shader.hpp"
#include "Engine/SubMesh.hpp"

namespace OGLSample
{

class FlatColorShader: public Shader
{
public:
    virtual void Bind(Ref<SubMesh>& subMesh) override;
};

}

#endif /* FlatColorShader_hpp */
