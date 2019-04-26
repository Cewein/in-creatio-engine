#include "window.h"

/*
this is a constuctor for the windows class
- winName : windows name
- maj and min : actual version of openGL
- w : width of the window
- l : lenght of the window
- iFL : to know if it's full screen
*/
Window::Window(char const * winName,short maj, short min, int w, int l, bool iFL)
{
	this->majContext = maj;
	this->minContext = min;
	this->width = w;
	this->height = l;
	this->isFullScreen = iFL;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majContext);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minContext);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	if(isFullScreen) display = glfwCreateWindow(width, height, winName, glfwGetPrimaryMonitor(), NULL);
	else display = glfwCreateWindow(width, height, winName, NULL, NULL);

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

	glfwSetInputMode(this->display, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}

//this is delta time is in second
//it's calculated timeActualFrame - timeLastFrame 
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


