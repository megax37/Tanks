#version 330 core

in vec3 exPosition;
in vec2 exTexcoord;
in vec3 exNormal;
in vec3 exNormalWorld;
in vec3 exEye;
in vec3 exLightDir;

out vec4 FragmentColor;

uniform vec3 DiffuseReflectivity;
uniform vec3 SpecularReflectivity;
uniform float SpecularExponent;

vec3 topHemisphere = vec3(0.0, 1.0, 0.0);
vec3 skyColor = vec3(0.6, 0.8, 0.9);
//vec3 groundColor = vec3(0.761, 0.698, 0.502);
vec3 groundColor = vec3(1.0, 0.843, 0.0);
const float PI = 3.141592653589793238462643383;

uniform sampler2D Texmap;
uniform int TexMode;

uniform DirectionalLight {
	vec3 LightDirection;
	vec3 LightColor;
};

void main(void)
{
	vec3 color;

	vec3 N = normalize(exNormal);
	//vec3 L = normalize(vec3(1.0, 0.5, 0.25));
	vec3 L = normalize(exLightDir);
	//vec3 L = normalize(vec3(1.0, 0.5, 0.25) - exPosition);
	//vec3 L = normalize(exLightDir - exPosition);
	vec3 E = normalize(exEye);

	float intensity = max(dot(L, N), 0.05);
	color = mix(DiffuseReflectivity * intensity, LightColor, 0.1);

	if(intensity > 0.0) {
		vec3 H = normalize(L + E);

		/* BLINN-PHONG SPECULAR */
		//color = color + SpecularReflectivity * pow(max(dot(H, N), 0.0), SpecularExponent * 4);

		/* GAUSSIAN DISTRIBUTION SPECULAR */
		float alpha = acos(dot(H, N));
		float m = smoothstep(0.0, 1000.0, SpecularExponent * 6);
		color = color + mix(SpecularReflectivity, LightColor, 0.2) * exp(-pow(alpha / m, 2.0));
	}

	/* HEMISPHERE AMBIENT LIGHTING */
	float theta = acos(dot(topHemisphere, normalize(exNormalWorld)));
	float factor;
	if(theta < PI / 2.0) {
		factor = 1.0 - 0.5 * sin(theta);
	} else {
		factor = 0.5 * sin(theta);
	}
	color = mix(color, mix(groundColor, skyColor, factor), 0.3);

	FragmentColor = vec4(0.0, 0.0, 0.0, 1.0);
}