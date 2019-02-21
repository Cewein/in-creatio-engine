#include <iostream>
#include "window.h"

int main()
{
	Window window("test", 4, 5, 500, 500, false);
	glViewport(0, 0, window.width, window.length);
	while (!glfwWindowShouldClose(window.display))
	{
		window.input();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	glfwTerminate();
	return 0;
}