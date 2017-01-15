#version 330 core

//in vec3 exPosition;
in vec2 exTexcoord;
//in vec3 exNormal;
//in vec3 exEye;
//in vec3 exLightDir;

out vec4 FragmentColor;

uniform sampler2D Texmap;
uniform float Life;

vec4 HotColor = vec3(1.0, 0.1, 0.0, 1.0);
vec4 MidColor = vec3(0.5, 0.1, 0.0, 1.0);
vec4 ColdColor = vec3(0.1, 0.0, 0.0, 1.0);

void main(void)
{
	vec4 color;
	vec4 texel;

	texel = texture(Texmap, exTexcoord);
	if(texel.a < 0.1) {
		discard;
	}
	else {
		if(life >= 0.5) {
			color = mix(MidColor, HotColor, ((life - 0.5) / 0.5));
		} else {
			color = mix(ColdColor, MidColor, (life / 0.5));
		}

		color.a = life;

		FragmentColor = color * texel;
	}
}
