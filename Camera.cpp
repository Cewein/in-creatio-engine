#include "Camera.h"
#include "glm/ext.hpp"

namespace Creatio
{
	void Camera::updateFront()
	{
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(front);
	}

	Camera::Camera(int width, int height)
	{
		projection = glm::perspective(glm::radians(90.0f), (float)width / (float)height, 0.01f, 1000000.0f);

		view = glm::mat4(1.f);

		position = glm::vec3(0.0f, 0.0f, 0.0f);
		front = glm::vec3(0.0f, 0.0f, -1.0f);
		up = glm::vec3(0.0f, 1.0f, 0.0f);
		speed = 5.f;
		defaultSpeed = speed;

		sensibility = 0.05f;

		yaw = -90.f;
		pitch = 0.f;

		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	}

	void Camera::update()
	{
		Input * input = Input::get();
	
		glm::vec3 newpos(0.f);

		speed = defaultSpeed;
		speed += input->getkey(SHIFT) * 10 * defaultSpeed;

		newpos += glm::vec3(input->getkey(UP) * input->getDeltaTime()) * front;
		newpos -= glm::vec3(input->getkey(DOWN) * input->getDeltaTime()) * front;
		newpos += glm::normalize(glm::cross(front, up)) * glm::vec3(input->getkey(RIGHT) * input->getDeltaTime());
		newpos -= glm::normalize(glm::cross(front, up)) * glm::vec3(input->getkey(LEFT) * input->getDeltaTime());
		this->position += newpos * speed;

		updateCamMouse(input->getOffsetX(), input->getOffsetY());

	}

	//offyw and offptch are the offset from last mouse pos
	void Camera::updateCamMouse(float offyw, float offptch)
	{
		setYaw(yaw + offyw * sensibility);
		setPitch(pitch + offptch * sensibility);
		updateFront();
	}

	void Camera::setPitch(float ptch)
	{
		if (ptch > 89.f)
			pitch = 89.f;
		else if (ptch < -89.f)
			pitch = -89.f;
		else pitch = ptch;
	}
}