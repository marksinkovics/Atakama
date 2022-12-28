#version 330 core

in vec2 UV;

out vec4 color;

uniform sampler2D textureSampler;
uniform vec2 uFrameSize;
uniform float uTime;

void main()
{
    color = texture(textureSampler, UV);
}
