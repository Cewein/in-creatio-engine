#include <glad/glad.h>
#include "window.h"

Window::Window(char const * winName,short maj, short min, int w, int l, bool iFL)
{
	this->majContext = maj;
	this->minContext = min;
	this->width = w;
	this->length = l;
	this->isFullScreen = iFL;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majContext);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minContext);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	if(isFullScreen) display = glfwCreateWindow(width, length, winName, glfwGetPrimaryMonitor(), NULL);
	else display = glfwCreateWindow(width, length, winName, NULL, NULL);

	if (display == NULL)
	{
		cout << "Failed to create GLFW Window\n";
		glfwTerminate();
		//need to do a propere error test
	}

	glfwMakeContextCurrent(display);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initilize GLAD");
		exit(1);
	}

}

//void Window::input()
//{
//	glfwSwapBuffers(this->display);
//	glfwPollEvents();
//
//	if (glfwGetKey(this->display, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(this->display, 1);
//}

double Window::getDeltaTime()
{
	double delta = 0;
	actualTime = this->getTime();
	if (this->pastTime)
	{
		delta = actualTime - pastTime;
	}
	pastTime = this->getTime();
	return delta;
}


