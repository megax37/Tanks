#version 330 core

in vec3 exPosition;
in vec2 exTexcoord;
in vec3 exNormal;
in vec3 exEye;
in vec3 exLightDir;

out vec4 FragmentColor;

uniform vec3 DiffuseReflectivity;
uniform vec3 SpecularReflectivity;
uniform float SpecularExponent;

uniform sampler2D Texmap;
uniform int TexMode;

void main(void)
{
	//vec3 color = (exPosition + vec3(1.0)) * 0.5;
	//vec3 color = vec3(exTexcoord, 0.0);

	vec3 color;

	vec3 N = normalize(exNormal);
	//vec3 L = normalize(vec3(1.0, 0.5, 0.25) - exPosition);
	vec3 L = normalize(exLightDir - exPosition);
	vec3 E = normalize(exEye);

	float intensity = max(dot(L, N), 0.0);
	color = DiffuseReflectivity * intensity * 0.9 + 0.1;

	if(intensity > 0.0) {
		vec3 H = normalize(L + E);
		float intSpec = max(dot(H, N), 0.0);
		color = color + SpecularReflectivity * pow(intSpec, SpecularExponent);
	}

	FragmentColor = vec4(color,1.0);
}
