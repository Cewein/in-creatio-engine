#include "Input.h"


//constructor
Input::Input(Window s)
{
	source = s;
	lastX = s.getWidth() / 2;
	lastY = s.getHeight() / 2;
	sensivity = 0.05f;
}

//keyboard input
// should be done with a file
void Input::processKeyboardInput(Camera * cam)
{
	cam->setDeltaSpeed(cam->getSpeed() * source.getDeltaTime());
	if (glfwGetKey(source.display, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(source.display, 1);
	if (glfwGetKey(source.display, GLFW_KEY_W) == GLFW_PRESS)
		cam->addPos(cam->getDeltaSpeed() * cam->getFront());
	if (glfwGetKey(source.display, GLFW_KEY_S) == GLFW_PRESS)
		cam->addPos(-(cam->getDeltaSpeed() * cam->getFront()));
	if (glfwGetKey(source.display, GLFW_KEY_A) == GLFW_PRESS)
		cam->addPos(-(glm::normalize(glm::cross(cam->getFront(), cam->getUp())) * cam->getDeltaSpeed()));
	if (glfwGetKey(source.display, GLFW_KEY_D) == GLFW_PRESS)
		cam->addPos(glm::normalize(glm::cross(cam->getFront(), cam->getUp())) * cam->getDeltaSpeed());
}


void Input::processMouseInput(Camera * cam)
{
	double xpos;
	double ypos;

	glfwGetCursorPos(source.display, &xpos, &ypos);
	if (xpos != lastX || ypos != lastY)
	{
		xoffset = xpos - lastX; 
		yoffset = lastY - ypos;

		xoffset *= sensivity;
		yoffset *= sensivity;

		cam->updateCamMouse(xoffset, yoffset);

		lastX = xpos;
		lastY = ypos;
	}
}

//this function is for calling all input process it run on the same thread as windows and pull every frame
void Input::pollEvent(Camera * cam)
{
	glfwSwapBuffers(source.display);
	glfwPollEvents();

	processKeyboardInput(cam);
	processMouseInput(cam);
}


Input::~Input()
{
}
