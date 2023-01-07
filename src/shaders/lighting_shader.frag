#version 330 core

in vec2 UV;
in vec3 fragColor;
in vec3 fragPosition;
in vec3 fragNormalWorld;

layout(location = 0) out vec4 o_Color;
layout(location = 1) out int o_MeshId;

// Model
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform mat3 uNormalMatrix;
// Light
uniform vec4 uLightPosition;
uniform vec4 uLightColor;
// Camera/Viewer
uniform vec3 uViewPosition;
// Texture sampler
uniform int uHasTexture;
uniform sampler2D textureSampler;
// MeshId
uniform int u_MeshId;
uniform int u_MeshSelected;

void main()
{
	vec3 color = fragColor;
	if (uHasTexture == 1) {
		color = texture(textureSampler, UV).rgb;
	}

    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * uLightColor.rgb;

    // diffuse
    vec3 norm = normalize(fragNormalWorld);
    vec3 lightDir = normalize(uLightPosition.xyz - fragPosition);
    float diff = clamp(dot(norm, lightDir), 0, 1);
    vec3 diffuse = diff * uLightColor.rgb;

    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(uViewPosition - fragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * uLightColor.rgb;

    vec3 result = (ambient + diffuse + specular) * color;
    o_Color = vec4(result, 1.0);
    if (u_MeshSelected == 1)
        o_Color = o_Color * vec4(1.0, 0.0, 0.0, 1.0);
    o_MeshId = u_MeshId;
}
