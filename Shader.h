#pragma once
#include <glm/glm.hpp>
#include "utils.h"

using namespace glm;

class Shader
{
private:
	size_t * vertexPtr;
	size_t * fragmentPtr;
	size_t * ShaderProgramPtr;

	//function for creating a shader program
	bool shaderCompilStat(size_t shader, const char * shaderName);
	bool programCompliStat(size_t program, const char * programName);
	void createVertexShader(const char * vertexShader);
	void createFragmentShader(const char * fragmentShader);
public:

	//getter and setter
	inline size_t getVertexPtr() { return  * vertexPtr; }
	inline size_t getFragementPtr() { return * fragmentPtr; }
	inline size_t getShaderProgPtr() { return * ShaderProgramPtr; }

	//add stuff to the shader
	inline void addInt(char * name, int value) { glUniform1i(glGetUniformLocation(*ShaderProgramPtr, name), value); }
	inline void addFloat(char * name, float value) { glUniform1f(glGetUniformLocation(*ShaderProgramPtr, name), value); }
	inline void addVec3(char * name, vec3 value) { glUniform3fv(glGetUniformLocation(*ShaderProgramPtr, name), 1, value); }
	inline void addVec4(char * name, vec4 value);
	inline void addMat3(char * name, mat3 value);
	inline void addMat4(char * name, mat4 value);

	Shader(size_t * vtxPtr, size_t * frgPtr, size_t * ShaderPtr, char * vertexShader, char * fragShader);
	~Shader();
};

