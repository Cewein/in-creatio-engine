#include <iostream>
#include <time.h>
#include "Input.h"
#include "window.h"
#include "Shader.h"
#include "Object.h"
#include "Camera.h"



int main()
{

	Creatio::Window window("test", 4, 5, 1920, 1080, true);
	Creatio::Input * input = Creatio::Input::init(window);
	Creatio::Shader tex("shader/vertex.glsl", "shader/raymarching.glsl");

	float plane[] = {
		-1.f, -1.f, 0.0f,  0.0f,  0.0f, -.0f,  0.0f,  0.0f,
		 1.f, -1.f, 0.0f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 1.f,  1.f, 0.0f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 1.f,  1.f, 0.0f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-1.f,  1.f, 0.0f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-1.f, -1.f, 0.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f
	};

	Creatio::Object cube2(plane, 6);
	Creatio::Camera cam(window.getWidth(), window.getHeight());

	tex.use();
	tex.setMat4((char *)"projection", cam.getProj());
	cam.setView(glm::lookAt(cam.getPos(), cam.getPos() + cam.getFront(), cam.getUp()));
	tex.setMat4((char *)"view", cam.getView());

	//render loop
	glViewport(0, 0, window.getWidth(), window.getHeight());
	while (!glfwWindowShouldClose(window.display))
	{
		input->pollEvent();
		cam.update();

		{
			glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}


		{
			tex.use();
			tex.setVec3((char *)"iResolution", (float)window.getWidth(), (float)window.getHeight(), 0.f);
			tex.setFloat((char *)"iTime", window.getTime());
			tex.setVec3((char *)"eye", cam.getPos());

			
			cam.setView(glm::lookAt(cam.getPos(), cam.getPos() + cam.getFront(), cam.getUp()));
			tex.setVec3((char *)"target", cam.getPos() + cam.getFront());
			tex.setVec3((char *)"up", cam.getUp());
		}

		cube2.start();
		cube2.translate(glm::vec3(0.f, 0.f, 0.f));
		tex.setMat4((char *)"transform", cube2.getTrans());
		cube2.show();

	}
	glfwTerminate();
	return 0;
}