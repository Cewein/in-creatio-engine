#include "Object.h"

namespace Creatio
{
	Object::Object(float * vecArray, int nbOfVertices)
	{
		//vertex binding
		numberOfVertices = nbOfVertices;
		transform = glm::mat4(1.0f);

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8 * numberOfVertices, vecArray, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		//other
		texture = Creatio::Texture(); //empty
	}

	Object::Object(float * vecArray, int nbOfVertices, Creatio::Texture tex)
	{

		//vertex binding
		numberOfVertices = nbOfVertices;
		transform = glm::mat4(1.0f);

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8 * numberOfVertices, vecArray, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		//other
		texture = tex; //need a texture in it
	}

	//indexed binding EBO only
	Object::Object(float * vecArray, float * index, int nbOfVertices)
	{
	}

	void Object::show()
	{
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, numberOfVertices);
	}
}
//not indexed binding VBO only

