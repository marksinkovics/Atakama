#version 330 core

in vec2 UV;

out vec4 color;

uniform sampler2D textureSampler;

float near = 0.1;
float far  = 100.0;
  
float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // back to NDC
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{
    float depth = texture(textureSampler, UV).r;
    depth = LinearizeDepth(depth) / far;
    color = vec4(vec3(depth), 1.0);
}
