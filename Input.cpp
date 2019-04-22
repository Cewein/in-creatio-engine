#include "Input.h"


//constructor
Input::Input(Window s)
{
	this->source = s;
}

//keyboard input
// should be done with a file
void Input::processKeyboardInput(Camera * cam)
{
	if (glfwGetKey(source.display, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(source.display, 1);
	if (glfwGetKey(source.display, GLFW_KEY_W) == GLFW_PRESS)
	{ 
		cam->addPos(cam->getSpeed() * cam->getUp());
		std::cout << "moved up" << std::endl;
	}
	if (glfwGetKey(source.display, GLFW_KEY_S) == GLFW_PRESS)
		cam->addPos(-(cam->getSpeed() * cam->getUp()));
	if (glfwGetKey(source.display, GLFW_KEY_A) == GLFW_PRESS)
		cam->addPos(-(glm::normalize(glm::cross(cam->getFront(), cam->getUp())) * cam->getSpeed()));
	if (glfwGetKey(source.display, GLFW_KEY_D) == GLFW_PRESS)
		cam->addPos(glm::normalize(glm::cross(cam->getFront(), cam->getUp())) * cam->getSpeed());
}


void Input::processMouseInput(Camera * cam)
{

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
