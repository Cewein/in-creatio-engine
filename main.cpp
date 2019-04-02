#include <iostream>
#include <time.h>
#include "window.h"
#include "Input.h"
#include "Shader.h"
#include "Object.h"



int main()
{

	Window window("test", 4, 5, 500, 500, false);
	Input input(window);
	Shader shader("shader/vertex.glsl", "shader/fragment.glsl");

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	}; ;

	Object tris(vertices, 3);

	//render loop
	glViewport(0, 0, window.getWidth(), window.getLength());
	while (!glfwWindowShouldClose(window.display))
	{
		input.pollEvent();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();
		tris.show();

		std::cout << window.getDeltaTime() << " s\n";
	}
	glfwTerminate();
	return 0;
}