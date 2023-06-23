#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec3 aColor;

// Model
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform vec4 uCameraPos;

// extents of grid in world coordinates
float gridSize = 100.0;

// size of one cell
float gridCellSize = 0.025;

// color of thin lines
vec4 gridColorThin = vec4(0.5, 0.5, 0.5, 1.0);

// color of thick lines (every tenth line)
vec4 gridColorThick = vec4(0.0, 0.0, 0.0, 1.0);

// minimum number of pixels between cell lines before LOD switch should occur.
const float gridMinPixelsBetweenCells = 2.0;

out vec2 uv;
out vec2 camPos;

void main()
{
	mat4 MVP = uProjection * uView;

	vec3 position = aPosition * gridSize;

	position.x += uCameraPos.x;
	position.z += uCameraPos.z;

	camPos = uCameraPos.xz;

	gl_Position = MVP * vec4(position, 1.0);
	uv = position.xz;
}
