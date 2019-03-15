#include <iostream>
#include <time.h>
#include "window.h"
#include "Input.h"

int main()
{
	Window window("test", 4, 5, 500, 500, false);
	Input input(window);

	glViewport(0, 0, window.getWidth(), window.getLength());
	while (!glfwWindowShouldClose(window.display))
	{
		input.pollEvent();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		std::cout << window.getDeltaTime() << " s\n";
	}
	glfwTerminate();
	return 0;
}