#version 450 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexcoord;
  
uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

out vec3 normal;
out vec2 uv;

void main()
{
    gl_Position = projection * view * transform * vec4(aPos, 1.0);
	uv = aTexcoord;
	normal = aNormal;
}