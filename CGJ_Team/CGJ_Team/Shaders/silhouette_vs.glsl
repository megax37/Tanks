#version 330 core

in vec3 inPosition;
in vec2 inTexcoord;
in vec3 inNormal;

uniform mat4 ModelMatrix;

uniform Camera {
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

void main(void)
{
	vec3 pos = inPosition + inNormal * 0.015;
	vec4 vmPosition = ViewMatrix * ModelMatrix * vec4(pos, 1.0);

	gl_Position = ProjectionMatrix * vmPosition;
}