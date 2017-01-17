#version 330 core

in vec3 inPosition;
in vec2 inTexcoord;
in vec3 inNormal;

out vec2 exTexcoord;

uniform mat4 ModelMatrix;

uniform Camera {
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

void main(void)
{
	exTexcoord = inTexcoord;

	vec4 vmPosition = ViewMatrix * ModelMatrix * vec4(inPosition, 1.0);

	gl_Position = ProjectionMatrix * vmPosition;
}