#version 330 core

in vec3 fragmentOffset;

layout(location = 0) out vec4 o_Color;
layout(location = 1) out int o_MeshId;

uniform vec4 uLightColor;

uniform int u_MeshId;
uniform int u_MeshSelected;

const float M_PI = 3.1415926538;

void main()
{
    float distant = sqrt(dot(vec2(fragmentOffset), vec2(fragmentOffset)));
    if (distant >= 1.0) {
        discard;
    }
    float cosDis = 0.5 * (cos(distant * M_PI) + 1.0);
    o_Color = vec4(uLightColor.xyz + cosDis, cosDis);
    // o_Color = uLightColor;
    o_MeshId = u_MeshId;
}
