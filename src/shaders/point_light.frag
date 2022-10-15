#version 330 core

in vec3 fragmentOffset;

out vec4 outColor;

uniform vec4 uLightColor;

const float M_PI = 3.1415926538;

void main()
{
    float distant = sqrt(dot(vec2(fragmentOffset), vec2(fragmentOffset)));
    if (distant >= 1.0) {
        discard;
    }
    float cosDis = 0.5 * (cos(distant * M_PI) + 1.0);
    outColor = vec4(uLightColor.xyz + cosDis, cosDis);
    // outColor = uLightColor;
}
