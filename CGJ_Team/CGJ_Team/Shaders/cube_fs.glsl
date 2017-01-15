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

uniform DirectionalLight {
	vec3 LightDirection;
	vec3 LightColor;
};

void main(void)
{
	vec3 color;

	vec3 N = normalize(exNormal);
	vec3 L = normalize(exLightDir);
	vec3 E = normalize(exEye);

	if(TexMode == 1) {
		color = vec3(texture(Texmap, exTexcoord));
	} else {
		color = vec3(DiffuseReflectivity);
	}

	float intensity = max(dot(L, N), 0.05);
	color = color * (intensity + 0.1) + LightColor * 0.1;

	if(intensity > 0.0) {
		vec3 H = normalize(L + E);

		/* BLINN-PHONG SPECULAR */
		//color = color + SpecularReflectivity * pow(max(dot(H, N), 0.0), SpecularExponent * 4);

		/* GAUSSIAN DISTRIBUTION SPECULAR */
		float alpha = acos(dot(H, N));
		float m = smoothstep(0.0, 1000.0, SpecularExponent * 6);
		color = color + mix(SpecularReflectivity, LightColor, 0.5) * exp(-pow(alpha / m, 2.0));
	}

	FragmentColor = vec4(color,1.0);
}
