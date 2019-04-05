#include <iostream>
#include <time.h>
#include "window.h"
#include "Input.h"
#include "Shader.h"
#include "Object.h"



int main()
{

	Window window("test", 4, 5, 800, 800, false);
	Input input(window);
	Shader bob("shader/vertex.glsl", "shader/nice.glsl");

	float vertices[] = {
		// first triangle
		 1.f,  1.f, 0.0f,  // top right
		 1.f, -1.f, 0.0f,  // bottom right
		-1.f,  1.f, 0.0f,  // top left 
		// second triangle
		 1.f, -1.f, 0.0f,  // bottom right
		-1.f, -1.f, 0.0f,  // bottom left
		-1.f,  1.0f, 0.0f   // top left
	};

	Object tris(vertices, 6);

	//render loop
	glViewport(0, 0, window.getWidth(), window.getLength());
	while (!glfwWindowShouldClose(window.display))
	{
		input.pollEvent();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		bob.use();
		bob.setVec3((char *)"iResolution", (float)window.getWidth(), (float)window.getLength(), 0.f);
		bob.setFloat((char *)"iTime", window.getTime());

		tris.rotate(window.getDeltaTime()*10, vec3(0.f, 0.f, 1.f));
		//tris.scale(vec3(0.5f,0.5f,0.5f));

		mat4 tmp = tris.getTrans();
		bob.setMat4((char *)"transform", tmp);
		tris.show();


		//std::cout << window.getDeltaTime() << " s\n";
	}
	glfwTerminate();
	return 0;
}