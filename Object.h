#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Texture.h"

using namespace glm;

namespace Creatio
{
	class Object
	{
	private:
		size_t VAO;
		size_t VBO;
		size_t VEO;

		Creatio::Texture texture;
		Creatio::Texture normal;
		Creatio::Texture specular;

		int numberOfVertices;
		mat4 transform;

	public:

		//need to be work on, more way to create a objet. with texture, or else
		Object(float * vecArray, int nbOfVertices);
		Object(float * vecArray, int nbOfVertices, Creatio::Texture tex);
		Object(float * vecArray,float * index, int nbOfVertices);

		//getter and setter
		inline size_t getVAO() { return VAO; }
		inline size_t getVBO() { return VBO; }
		inline size_t getVEO() { return VEO; }
		inline mat4 getTrans() { return transform; }
		inline Creatio::Texture getTex() { return texture; }

		inline void setTrans(glm::mat4 newTrans) { transform = newTrans; }
		inline void setTexture(Creatio::Texture tex) { texture = tex; }

		//small math like transform, rotate, scale, ect...
		inline void start() { transform = mat4(1.0f); }
		inline void rotate(float degree, vec3 rotate) { transform = glm::rotate(transform, glm::radians(degree), rotate); };
		inline void scale(vec3 scale) { transform = glm::scale(transform, scale); }
		inline void translate(vec3 translate) { transform = glm::translate(transform, translate); }
		inline Object clone() { return * this; } //not sure about this one...

		//render the object
		void show();
	};
}