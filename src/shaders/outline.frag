#version 330 core

in vec2 UV;

layout(location = 0) out vec4 o_Color;
layout(location = 1) out int o_MeshId;

uniform vec2 u_TextureSize;
uniform int u_SelectedMeshId;
uniform sampler2D u_TextureSampler;
uniform isampler2D u_MeshIdSampler;

void main()
{
    vec4 outlineColor = vec4(254.0/255.0, 159.0/255.0, 44.0/255.0, 1.0);
    int width = 3;
    vec2 size = 1.0 / textureSize(u_MeshIdSampler, 0);

    int meshId = texture(u_MeshIdSampler, UV).r;
    o_MeshId = meshId;
    o_Color = texture(u_TextureSampler, UV);;

    if (u_SelectedMeshId == 0)
    {
        return;
    }

    if (meshId == u_SelectedMeshId)
    {
        return;
    }

    for (int i = -width; i <= width; i++)
    {
        for (int j = -width; j <= width; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }

            vec2 offset = UV + (vec2(i, j) * size);
            int offsetMeshId = texture(u_MeshIdSampler, offset).r;
            if (offsetMeshId == u_SelectedMeshId)
            {
                o_Color = outlineColor;
                return;
            }
        }
    }
}
