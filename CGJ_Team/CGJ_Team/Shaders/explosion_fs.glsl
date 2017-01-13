#version 330 core

//in vec3 exPosition;
in vec2 exTexcoord;
//in vec3 exNormal;
//in vec3 exEye;
//in vec3 exLightDir;

out vec4 FragmentColor;

uniform vec4 Color;
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
		color = vec3(Color);
	}

	float intensity = max(dot(L, N), 0.05);
	//color = mix(color * intensity, LightColor, 0.15);
	color = color * (intensity + 0.1) + LightColor * 0.1;

	if(intensity > 0.0) {
		vec3 H = normalize(L + E);

		/* BLINN-PHONG SPECULAR */
		//color = color + LightColor * pow(max(dot(H, N), 0.0), 15 * 4);

		/* GAUSSIAN DISTRIBUTION SPECULAR */
		float alpha = acos(dot(H, N));
		//float m = smoothstep(1, 1000.0, SpecularExponent * 6);
		color = color + LightColor * exp(-pow(alpha / 0.15, 2.0)) * 0.75;
	}

	FragmentColor = vec4(color,1.0);
}
