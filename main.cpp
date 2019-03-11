#include <iostream>
#include <time.h>
#include "window.h"

int main()
{
	Window window("test", 4, 5, 500, 500, false);
	Window window2("test", 4, 5, 500, 500, false);
	glViewport(0, 0, window.getWidth(), window.getLength());
	while (!glfwWindowShouldClose(window.display))
	{
		system("cls");
		clock_t begin = clock();
		window.input();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		clock_t end = clock();
		double timeSpend = (double)(end - begin) / CLOCKS_PER_SEC;
		std::cout << "Time spend rendering : \t" << timeSpend << " ms\n";
	}
	glfwTerminate();
	return 0;
}