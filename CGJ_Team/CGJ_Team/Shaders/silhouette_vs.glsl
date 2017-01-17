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
	mat4 scale = mat4(1.02, 0.0, 0.0, 0.0,
					  0.0, 1.02, 0.0, 0.0,
					  0.0, 0.0, 1.02, 0.0,
					  0.0, 0.0, 0.0, 1.0);
					  
	mat4 model = ModelMatrix * scale;
	vec4 vmPosition = ViewMatrix * model * vec4(inPosition, 1.0);

	gl_Position = ProjectionMatrix * vmPosition;
}