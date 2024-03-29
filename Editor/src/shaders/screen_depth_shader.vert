#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec3 aColor;

out vec2 UV;

void main(){
    gl_Position = vec4(aPosition, 1);
    UV = aUV;
}
