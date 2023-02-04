#version 330 core

in vec2 UV;

layout(location = 0) out vec4 o_Color;
layout(location = 1) out int o_MeshId;

// MeshId
uniform int u_MeshId;
uniform int u_SelectedMeshId;

uniform sampler2D textureSampler;

void main()
{
    o_Color = texture(textureSampler, UV);
    o_MeshId = u_MeshId;
}
