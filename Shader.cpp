#pragma warning(disable : 4996)
#include <glad/glad.h>
#include "Shader.h"



Shader::Shader(size_t * vtxPtr, size_t * frgPtr, size_t * ShaderPtr, char * vertexShader, char * fragShader)
{
	vertexPtr = vtxPtr;
	fragmentPtr = frgPtr;
	ShaderProgramPtr = ShaderPtr;

	createVertexShader(vertexShader);
	createFragmentShader(fragShader);
}


Shader::~Shader()
{
}

//this function is for debugging and compilation validation of frag and vertex shader
bool Shader::shaderCompilStat(size_t shader, const char * shaderName)
{
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader, 512, NULL, infoLog);
		printf("ERROR [%s] DID NOT COMPILE!\n%s\n", shaderName, infoLog);
		return false;
	}
	return true;
}

//this function is for debugging and compilation validation of the shader program on the CG
bool Shader::programCompliStat(size_t program, const char * programName)
{
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		printf("ERROR [%s] DID NOT COMPILE!\n%s\n", programName, infoLog);
		return false;
	}
	return true;
}

//this function create a Vertex Shader it just to know were is the shader File
void Shader::createVertexShader(const char * vertexShader)
{
	*vertexPtr = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(*vertexPtr, 1, &vertexShader, NULL);
	glCompileShader(*vertexPtr);

	if (!shaderCompilStat(*vertexPtr, "VERTEX SHADER"))
	{
		//need to do error output
	}
}

//this function create a Fragment Shader it just to know were is the shader File
void Shader::createFragmentShader(const char * fragmentShader)
{
	*fragmentPtr = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(*fragmentPtr, 1, &fragmentShader, NULL);
	glCompileShader(*fragmentPtr);

	if(!shaderCompilStat(*fragmentPtr, "FRAGMENT SHADER"))
	{
		//need to do error output
	}
}