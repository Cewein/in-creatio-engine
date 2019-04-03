#include "Object.h"


Object::Object(float * vecArray, int nbOfVertices)
{
	numberOfVertices = nbOfVertices;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * numberOfVertices, vecArray, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Object::show()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, numberOfVertices);
}

