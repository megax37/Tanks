#version 330 core

in vec3 exPosition;
in vec2 exTexcoord;
in vec3 exNormal;

out vec4 FragmentColor;

uniform vec4 Color;
uniform sampler2D Texmap;
uniform int TexMode;

void main(void)
{
	//vec3 color = vec3(1.0);
	//vec3 color = (exPosition + vec3(1.0)) * 0.5;
	//vec3 color = vec3(exTexcoord, 0.0);
	vec3 color;
	if(TexMode == 1) {
		//color = vec3(1.0);
		color = vec3(texture(Texmap, exTexcoord));
	}
	else if(Color.w == -1.0) {
		color = (exNormal + vec3(1.0)) * 0.5;
	} else {
		color = 0.75 * vec3(Color) + 0.25 * (exNormal + vec3(1.0)) * 0.5;
	}
	FragmentColor = vec4(color,1.0);
}

//vec3 N = normalize(exNormal);
//vec3 direction = vec3(1.0, 0.5, 0.25);
//float intensity = max(dot(direction, N), 0.0);
//FragmentColor = vec4(vec3(intensity), 1.0);
