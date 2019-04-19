#include "Input.h"


//constructor
Input::Input(Window s)
{
	this->source = s;
}

//keyboard input
// should be done with a file
void Input::processKeyboardInput(Window win,Camera cam)
{
	if (glfwGetKey(source.display, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(source.display, 1);
	if (glfwGetKey(win.display, GLFW_KEY_W) == GLFW_PRESS)
		cam.addPos(cam.getSpeed() * cam.getUp);
	if (glfwGetKey(win.display, GLFW_KEY_S) == GLFW_PRESS)
		cam.addPos (cam.getSpeed * cam.;
	if (glfwGetKey(win.display, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(win.display, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}


void Input::processMouseInput(Camera cam)
{

}

//this function is for calling all input process it run on the same thread as windows and pull every frame
void Input::pollEvent(Camera cam)
{
	glfwSwapBuffers(source.display);
	glfwPollEvents();

	processKeyboardInput();
	processMouseInput();
}


Input::~Input()
{
}
