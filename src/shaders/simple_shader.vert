#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec3 aColor;

uniform mat4 MVP;

out vec3 fragmentColor;

void main()
{
  gl_Position = MVP * vec4(aPosition, 1);
  fragmentColor = aColor;
}
