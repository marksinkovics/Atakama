#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec3 aColor;

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

out vec2 UV;
out vec3 fragPosition;
out vec3 Normal;
out vec3 ViewPosition;

void main()
{
	// Updating out variables
  	UV = aUV;
	fragPosition = vec3(uModel * vec4(aPosition, 1.0));
	Normal = normalize(mat3(uNormalMatrix) * aNormal);
	ViewPosition = uViewPosition;
	gl_Position = uProjection * uView * uModel * vec4(aPosition, 1);
}
