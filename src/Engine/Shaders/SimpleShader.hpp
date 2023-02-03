#ifndef ATAKAMA_SIMPLE_SHADER_HPP
#define ATAKAMA_SIMPLE_SHADER_HPP

#include "Engine/Shader.hpp"
#include "Engine/SubMesh.hpp"

namespace Atakama
{

class SimpleShader: public Shader
{
public:
    virtual void Bind(Ref<SubMesh>& subMesh) override;
};

}

#endif
