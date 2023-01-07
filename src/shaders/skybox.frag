#version 330 core

in vec3 UV;

layout(location = 0) out vec4 o_Color;
layout(location = 1) out int o_MeshId;


// Texture sampler
uniform int uHasTexture;
uniform samplerCube textureSampler;

void main()
{
    o_Color = texture(textureSampler, UV);
    o_MeshId = 0;
}
