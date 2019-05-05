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
	if (xpos != lastX || ypos != lastY)
	{
		
		mouseY = ypos;
		mouseX = xpos;

		xoffset = xpos - lastX;
		yoffset = lastY - ypos;

		lastX = xpos;
		lastY = ypos;

		//std::cout << "offset X:" << xoffset << std::endl;
		//std::cout << "offset Y:" << yoffset << std::endl;
		//std::cout << "mouseY:" << mouseY << std::endl;
		//std::cout << "mouseX:" << mouseX << std::endl;
		//std::cout << "lastX:" << lastX << std::endl;
		//std::cout << "lastY:" << lastY << std::endl;
	}
	else
	{
		xoffset = 0;
		yoffset = 0;
	}
}

//this function is for calling all input process it run on the same thread as windows and pull every frame
void Input::pollEvent()
{
	glfwSwapBuffers(source.display);
	glfwPollEvents();
	source.setDeltaTime();
	std::cout << 1 / source.getDeltaTime() << " FPS\n";
	processKeyboardInput();
	processMouseInput();
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
	return xoffset;
}

int Input::getkey(int i)
{
	return (int)key[i];
}

double Input::getDeltaTime()
{
	return source.getDeltaTime();
}

