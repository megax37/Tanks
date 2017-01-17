#version 330 core

in vec3 inPosition;
in vec2 inTexcoord;
in vec3 inNormal;

out vec3 exPosition;
out vec2 exTexcoord;
out vec3 exNormal;
out vec3 exNormalWorld;
out vec3 exEye;
out vec3 exLightDir;

uniform mat4 ModelMatrix;
uniform mat3 NormalMatrix;

uniform Camera {
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

uniform DirectionalLight {
	vec3 LightDirection;
	vec3 LightColor;
};

void main(void)
{
	//exPosition = inPosition;
	exTexcoord = inTexcoord;
	exNormalWorld = normalize(NormalMatrix * inNormal);
	exNormal = normalize(vec3(transpose(inverse(ViewMatrix * ModelMatrix)) * vec4(inNormal, 1.0)));
	mat4 scale = mat4(1.05, 0.0, 0.0, 0.0,
					  0.0, 1.05, 0.0, 0.0,
					  0.0, 0.0, 1.05, 0.0,
					  0.0, 0.0, 0.0, 1.0);
					  
	mat4 model = ModelMatrix * scale;
	vec4 vmPosition = ViewMatrix * model * vec4(inPosition, 1.0);

	exPosition = vec3(vmPosition);
	exEye = vec3(-vmPosition);
	exLightDir = vec3(ViewMatrix * vec4(LightDirection, 0.0));

	gl_Position = ProjectionMatrix * vmPosition;
}