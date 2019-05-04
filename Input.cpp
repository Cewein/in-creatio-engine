#include "Input.h"
//init the singleton to nothing
Input * Input::singleton = nullptr;

//private initiator
Input::Input(Window s)
{
	source = s;
	lastX = s.getWidth() / 2;
	lastY = s.getHeight() / 2;
	xoffset = 0.f;
	yoffset = 0.f;
	key[NUMBERINPUT];
}

//keyboard input
// should be done with a file
void Input::processKeyboardInput()
{
	if (glfwGetKey(source.display, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(source.display, 1);

	if (glfwGetKey(source.display, GLFW_KEY_W) == GLFW_PRESS)
		key[UP] = true;
	else key[UP] = false;

	if (glfwGetKey(source.display, GLFW_KEY_S) == GLFW_PRESS)
		key[DOWN] = true;
	else key[DOWN] = false;

	if (glfwGetKey(source.display, GLFW_KEY_A) == GLFW_PRESS)
		key[LEFT] = true;
	else key[LEFT] = false;

	if (glfwGetKey(source.display, GLFW_KEY_D) == GLFW_PRESS)
		key[RIGHT] = true;
	else key[RIGHT] = false;
}


void Input::processMouseInput()
{
	double xpos;
	double ypos;

	glfwGetCursorPos(source.display, &xpos, &ypos);
	
	mouseY = ypos;
	mouseX = xpos;

	xoffset = mouseX - lastX;
	xoffset = lastY - mouseY;
}

//this function is for calling all input process it run on the same thread as windows and pull every frame
void Input::pollEvent()
{
	glfwSwapBuffers(source.display);
	glfwPollEvents();

	processKeyboardInput();
	//processMouseInput();
}

float Input::getmouseX()
{
	return Input::mouseX;
}

float Input::getmouseY()
{
	return Input::mouseY;
}

float Input::getOffsetY()
{
	return Input::yoffset;
}

float Input::getOffsetX()
{
	return Input::xoffset;
}

int Input::getkey(int i)
{
	return (int)Input::key[i];
}

double Input::getDeltaTime()
{
	return Input::source.getDeltaTime();
}

