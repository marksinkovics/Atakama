#version 330 core

in vec2 UV;
in vec3 fragColor;
in vec3 fragPosition;
in vec3 fragNormalWorld;

out vec4 outColor;

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
    outColor = vec4(result, 1.0);
}
