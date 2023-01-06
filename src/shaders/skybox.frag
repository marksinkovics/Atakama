#version 330 core

in vec3 UV;

out vec4 color;

// Texture sampler
uniform int uHasTexture;
uniform samplerCube textureSampler;

void main()
{
    color = texture(textureSampler, UV);
}
