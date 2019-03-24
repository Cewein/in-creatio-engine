#pragma once
#include <glm/glm.hpp>

using namespace glm;

class Shader
{
private:
	size_t vertexPtr;
	size_t fragmentPtr;
	size_t shaderProgramPtr;

	//function for creating a shader program
	bool shaderCompilStat(size_t shader, const char * shaderName);
	bool programCompliStat(size_t program, const char * programName);

public:

	//shader creation function
	void createVertexShader(char * vertexShader);
	void createFragmentShader(char * fragmentShader);
	void createProgramShader();

	//getter and setter
	inline size_t getVertexPtr() { return  vertexPtr; }
	inline size_t getFragementPtr() { return fragmentPtr; }
	inline size_t getShaderProgPtr() { return shaderProgramPtr; }

	//add stuff to the shader
	inline void setInt(char * name, int value) { glUniform1i(glGetUniformLocation(shaderProgramPtr, name), value); }
	inline void setFloat(char * name, float value) { glUniform1f(glGetUniformLocation(shaderProgramPtr, name), value); }
	inline void setVec3(char * name, vec3 value) { glUniform3fv(glGetUniformLocation(shaderProgramPtr, name), 1, &value[0]); }
	inline void setVec3(char * name, float x, float y, float z) { glUniform3f(glGetUniformLocation(shaderProgramPtr, name), x, y, z); }
	inline void setVec4(char * name, vec4 value) { glUniform4fv(glGetUniformLocation(shaderProgramPtr, name), 1, &value[0]); }
	inline void setVec4(char * name, float x, float y, float z, float w) { glUniform4f(glGetUniformLocation(shaderProgramPtr, name), x, y, z, w); }
	inline void setMat3(char * name, mat3 value) { glUniformMatrix3fv(glGetUniformLocation(shaderProgramPtr, name), 1, GL_FALSE, &value[0][0]); }
	inline void setMat4(char * name, mat4 value) { glUniformMatrix4fv(glGetUniformLocation(shaderProgramPtr, name), 1, GL_FALSE, &value[0][0]); }

	//usage function
	inline void use() { glUseProgram(shaderProgramPtr); }

	Shader(char * vertexShader, char * fragShader);

	//shoud we need a destructor ?
};

