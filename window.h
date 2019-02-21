#pragma once
#ifndef WINDOWH
#define WINDOWH
#include <iostream>
#include <GLFW/glfw3.h>

using std::cout;

class Window
{
public:
	Window() {}
	Window(char const * winName, int maj, int min, int w, int l, bool iFL);

	//openGl context
	int minContext;
	int majContext;

	//windows info
	int width;
	int length;
	bool isFullScreen;
	char * winName;

	//window struct
	GLFWwindow * display;

	void input();
};


#endif // !window
