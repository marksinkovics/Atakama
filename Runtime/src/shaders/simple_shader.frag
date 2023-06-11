#version 330 core

in vec3 fragmentColor;

layout(location = 0) out vec4 o_Color;
layout(location = 1) out int o_MeshId;

// MeshId
uniform int u_MeshId;
uniform int u_SelectedMeshId;

void main()
{
    o_Color = vec4(fragmentColor, 1.0);
    o_MeshId = u_MeshId;
}
