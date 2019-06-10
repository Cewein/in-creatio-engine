#version 450 core

uniform float iTime;
uniform vec3 iResoltion;
uniform vec3 iColor;
uniform vec3 lightPos;

uniform sampler2D tex;
uniform sampler2D normalTex;

in vec2 uv;
in vec3 normal;
in vec3 pos;

out vec4 FragColor;

void main()
{
	//ambient
	float ambientStrengh = 0.1;
	vec3 ambient = ambientStrengh * iColor;

	//normal
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - normalize(pos));


	//diffuse
	float diff  = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * iColor;

	vec3 result = ambient + diffuse;
	FragColor = mix(texture(tex,uv), texture(normalTex,uv),0.2);
	FragColor = vec4(FragColor.xyz * result, FragColor.w);
}
