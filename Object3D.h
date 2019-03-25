#pragma once
#include <glad/glad.h>
class Object3D
{
private:
	size_t VAO;
	size_t VBO;

	int numberOfFaces;


public:

	Object3D(double * vecArray, int nbOfFaces);

	//getter

	inline size_t getVOA() { return VAO; }
	inline size_t getVBO() { return VBO; }
};

