#version 330 core

in vec2 exTexcoord;

out vec4 FragmentColor;

uniform sampler2D Texmap;
uniform int TexMode;
uniform float Life;

vec4 HotColor = vec4(0.8, 0.1, 0.0, 1.0);
vec4 MidColor = vec4(0.2, 0.0, 0.0, 1.0);
vec4 ColdColor = vec4(0.1, 0.0, 0.0, 1.0);

void main(void)
{
	vec4 color;
	vec4 texel;

	texel = texture(Texmap, exTexcoord);
	if(texel.a < 0.1) {
		discard;
	}
	else {
		if(Life >= 0.5) {
			color = mix(MidColor, HotColor, ((Life - 0.5) / 0.5));
		} else {
			color = mix(ColdColor, MidColor, (Life / 0.5));
		}

		color.a = Life;

		FragmentColor = color * texel;
	}
}
