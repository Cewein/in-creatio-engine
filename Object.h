#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace glm;

class Object
{
private:
	size_t VAO;
	size_t VBO;

	int numberOfVertices;

public:

	mat4 transform;

	Object(float * vecArray, int nbOfVertices);

	//getter
	inline size_t getVAO() { return VAO; }
	inline size_t getVBO() { return VBO; }
	inline mat4 getTrans() { return transform; }

	//small math like transform, rotate, scale, ect...
	inline void rotate(float degree, vec3 rotate) { transform = glm::rotate(transform, glm::radians(degree), rotate); };
	inline void scale(vec3 scale) { transform = glm::scale(transform, scale); }

	//render the object
	void show();
};