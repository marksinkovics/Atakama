#ifndef SIMPLE_SHADER
#define SIMPLE_SHADER

#include "Engine/Shader.hpp"
#include "Engine/SubMesh.hpp"

namespace OGLSample
{

class SimpleShader: public Shader
{
public:
    virtual void Bind(Ref<SubMesh>& subMesh) override;
};

}

#endif
