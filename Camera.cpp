#include "Camera.h"

Camera::Camera(int width, int height)
{
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

	view = glm::mat4(1.f);

	position = glm::vec3(0.0f, 0.0f, 3.0f);
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
}