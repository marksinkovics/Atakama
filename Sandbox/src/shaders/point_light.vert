#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec3 aColor;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
// Light
uniform vec4 uLightPosition;
uniform vec4 uLightColor;
// Camera/Viewer
uniform vec3 uViewPosition;

out vec3 fragmentColor;
out vec3 fragmentOffset;

void main()
{
    float scale = 0.05;
    vec3 cameraRightWorld = vec3(uView[0][0], uView[1][0], uView[2][0]);
    vec3 cameraUpWorld = vec3(uView[0][1], uView[1][1], uView[2][1]);
    vec3 positionWorld = uLightPosition.xyz
        + scale * aPosition.x * cameraRightWorld
        + scale * aPosition.y * cameraUpWorld;

    gl_Position = uProjection * uView * vec4(positionWorld, 1.0);
    // gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);

    fragmentOffset = aPosition;
    fragmentColor = vec3(uLightColor);
}
