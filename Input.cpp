#include "Input.h"


//constructor
Input::Input(Window s)
{
	this->source = s;
}

//keyboard input
// should be done with a file
void Input::processKeyboardInput()
{
	if (glfwGetKey(source.display, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(source.display, 1);
}


void Input::processMouseInput()
{

}

//this function is for calling all input process it run on the same thread as windows and pull every frame
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
