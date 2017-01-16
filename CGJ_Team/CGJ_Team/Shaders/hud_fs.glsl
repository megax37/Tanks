#version 330 core

in vec2 exTexcoord;

out vec4 FragmentColor;

uniform sampler2D Texmap;
uniform int TexMode;

void main(void)
{
	vec3 color;
	
	if(TexMode == 1) {
		color = vec3(texture(Texmap, exTexcoord));
	}

	FragmentColor = vec4(color,1.0);
}
