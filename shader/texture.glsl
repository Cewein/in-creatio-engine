#version 450 core

uniform float iTime;
uniform float iResoltion;

uniform sampler2D tex;

in vec2 uv;
in vec3 normal;

out vec4 FragColor;

void main()
{
	FragColor = texture(tex,uv);
}
