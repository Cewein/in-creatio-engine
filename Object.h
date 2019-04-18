#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Texture.h"

using namespace glm;

class Object
{
private:
	size_t VAO;
	size_t VBO;
	size_t VEO;

	Texture texture;

	int numberOfVertices;
	mat4 transform;

public:

	//need to be work on, more way to create a objet. with texture, or else
	Object(float * vecArray, int nbOfVertices);
	Object(float * vecArray,float * index, int nbOfVertices);

	//getter
	inline size_t getVAO() { return VAO; }
	inline size_t getVBO() { return VBO; }
	inline size_t getVEO() { return VEO; }
	inline mat4 getTrans() { return transform; }

	//small math like transform, rotate, scale, ect...
	inline void start() { transform = mat4(1.0f); }
	inline void rotate(float degree, vec3 rotate) { transform = glm::rotate(transform, glm::radians(degree), rotate); };
	inline void scale(vec3 scale) { transform = glm::scale(transform, scale); }
	inline void translate(vec3 translate) { transform = glm::translate(transform, translate); }
	inline Object clone() { return * this; } //not sure about this one...

	//render the object
	void show();
};