#include "Input.h"



Input::Input(Window s)
{
	this->source = s;
}

void Input::processKeyboardInput()
{
	if (glfwGetKey(source.display, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(source.display, 1);
}

void Input::processMouseInput()
{

}

void Input::pollEvent()
{
	glfwSwapBuffers(source.display);
	glfwPollEvents();

	processKeyboardInput();
	processMouseInput();
}


Input::~Input()
{
}
