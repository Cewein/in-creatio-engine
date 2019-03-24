#pragma warning(disable : 4996)
#include <glad/glad.h>
#include "utils.h"
#include "Shader.h"



Shader::Shader(char * vertexShader, char * fragShader)
{
	//make file stream
	FILE * vertex = NULL;
	vertex = fopen(vertexShader, "rb");
	FILE * fragment = NULL;
	fragment = fopen(fragShader, "rb");

	//check if file as been read
	if (vertex != NULL && fragment != NULL)
	{
		createVertexShader(freadInArray(vertex));
		createFragmentShader(freadInArray(fragment));
		createProgramShader();

		//close file stream
		fclose(vertex);
		fclose(fragment);

		//delete shader because the are compiled in the program
		glDeleteShader(vertexPtr);
		glDeleteShader(fragmentPtr);
	}
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

// this create a shader program, it need to be done avec creating a vertex and a fragment shader
void Shader::createProgramShader()
{
	shaderProgramPtr = glCreateProgram();
	glAttachShader(shaderProgramPtr, vertexPtr);
	glAttachShader(shaderProgramPtr, fragmentPtr);
	glLinkProgram(shaderProgramPtr);

	programCompliStat(shaderProgramPtr, "SHADER LINK PROGRAM");
}

//this function create a Vertex Shader it just the shader File data
void Shader::createVertexShader(char * vertexShader)
{
	vertexPtr = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexPtr, 1, &vertexShader, NULL);
	glCompileShader(vertexPtr);

	if (!shaderCompilStat(vertexPtr, "VERTEX SHADER"))
	{
		//need to do error output
	}
}

//this function create a Fragment Shader it just to know the shader File data
void Shader::createFragmentShader(char * fragmentShader)
{
	fragmentPtr = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentPtr, 1, &fragmentShader, NULL);
	glCompileShader(fragmentPtr);

	if(!shaderCompilStat(fragmentPtr, "FRAGMENT SHADER"))
	{
		//need to do error output
	}
}