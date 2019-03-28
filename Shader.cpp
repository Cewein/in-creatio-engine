#pragma warning(disable : 4996)
#include "utils.h"
#include "Shader.h"



Shader::Shader(const char * vertexShader, const char * fragShader)
{
	//make file stream
	FILE * vertex = NULL;
	vertex = fopen(vertexShader, "rb");
	FILE * fragment = NULL;
	fragment = fopen(fragShader, "rb");

	//check if file as been read
	if (vertex != NULL && fragment != NULL)
	{
		createShader(freadInArray(vertex), GL_VERTEX_SHADER);
		createShader(freadInArray(fragment), GL_FRAGMENT_SHADER);
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
		printf("ERROR [%s] DID NOT COMPILE!\n", shaderName);
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

//this function create a Vertex Shader it just the shader File
//And the shader macro, there is two : GL_VERTEX_SHADER and GL_FRAGMENT_SHADER
void Shader::createShader(char * shader, int macro)
{
	size_t * shaderPtr;
	if (macro == GL_VERTEX_SHADER)
	{
		shaderPtr = &vertexPtr;
		*shaderPtr = glCreateShader(macro);

	}
	else if (macro == GL_FRAGMENT_SHADER)
	{
		shaderPtr = &fragmentPtr;
		*shaderPtr = glCreateShader(macro);
	}

	glShaderSource(*shaderPtr, 1, &shader, NULL);
	glCompileShader(*shaderPtr);

	if (!shaderCompilStat(*shaderPtr, "VERTEX SHADER"))
	{
		//need to do error output
	}
}
