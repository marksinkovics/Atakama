#version 330 core

in vec2 UV;
in vec3 fragPosition;
in vec3 Normal;
in vec3 ViewPosition;

out vec4 color;

uniform sampler2D textureSampler;

uniform vec4 uLightPosition;
uniform vec4 uLightColor;

void main()
{
	vec3 objectColor = texture(textureSampler, UV).rgb;

    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * uLightColor.rgb;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(uLightPosition.xyz - fragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * uLightColor.rgb;

    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(ViewPosition - fragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    vec3 specular = specularStrength * spec * uLightColor.rgb;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    color = vec4(result, 1.0);
}
