#version 330 core

in vec2 UV;

layout(location = 0) out vec4 o_Color;

uniform sampler2D textureSampler;

void main()
{
    o_Color = texture(textureSampler, UV);
}
