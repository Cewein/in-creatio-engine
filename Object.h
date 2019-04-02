#pragma once
#include <glad/glad.h>
class Object
{
private:
	size_t VAO;
	size_t VBO;

	int numberOfVertices;


public:

	Object(float * vecArray, int nbOfVertices);

	//getter
	inline size_t getVAO() { return VAO; }
	inline size_t getVBO() { return VBO; }

	//render the object
	void show();
};